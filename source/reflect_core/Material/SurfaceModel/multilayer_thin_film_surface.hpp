/*!
  \file multilayer_thin_film_surface.hpp
  \author takemura
  */

#ifndef _REFLECT_MULTILAYER_THIN_FILM_SURFACE_HPP_
#define _REFLECT_MULTILAYER_THIN_FILM_SURFACE_HPP_

// Standard C++ library
#include <array>
#include <complex>
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "reflect_config.hpp"
#include "surface_model.hpp"
#include "Color/spectral_distribution.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class IntersectionInfo;
class Sampler;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
class MultilayerThinFilmSurface : public SurfaceModel 
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a multilayer thin film surface
  MultilayerThinFilmSurface(const QSettings& settings, const QString& prefix);


  //! Make a thin film bsdf
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeSpecularBrdf(
      const Vector3* vin,
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the multilayer thin film surface type
  SurfaceType type() const override;

 private:
  struct Layer
  {
    double thickness_;
    std::array<std::complex<double>, kSpectraSize> complex_refractive_index_;
  };

  //! Calculate composite reflectance and transmittance
  void calculateCompositeProperties(const double theta_i,
                                    const std::size_t lambda,
                                    const std::vector<Layer>& multilayer,
                                    const std::size_t number,
                                    std::complex<double>& reflectance_p,
                                    std::complex<double>& reflectance_s) const;

  //! Initialize
  void initialize(const QSettings& settings, const QString& prefix);

  //! Return the exterior medium layer
  Layer makeExteriorMediumLayer(const QSettings& settings, const QString& prefix);

  //! Return the interior medium layer
  Layer makeInteriorMediumLayer(const QSettings& settings, const QString& prefix);

  //! Return the layer list
  std::vector<Layer> makeMultilayer(const QSettings& settings,
                                    const QString& prefix);

  //! Return the thin film layer
  Layer makeThinFilmLayer(const QSettings& settings, const QString& prefix);

  //! Set composite reflectance and transmittance
  void setCompositeProperties(const std::vector<Layer>& multilayer);
  

  static constexpr std::size_t kDeltaAngle = 5;
  static constexpr std::size_t kN = (90 / kDeltaAngle) + 1;

  SpectralDistribution reflectance_[kN];
};

//!
std::complex<double> calculateParallelBoundaryReflectance(
    const std::complex<double>& n_i,
    const std::complex<double>& n_t,
    const double theta_i,
    const double theta_t);

//!
std::complex<double> calculatePerpendicularBoundaryReflectance(
    const std::complex<double>& n_i,
    const std::complex<double>& n_t,
    const double theta_i,
    const double theta_t);

//!
std::complex<double> calculateCompositeReflectance(
    const std::complex<double>& reflectance,
    const std::complex<double>& r,
    const std::complex<double>& phase_difference);

//!
std::complex<double> calculatePhaseDifference(const double wavelength,
                                              const double thickness,
                                              const std::complex<double>& n,
                                              const double theta_t);

//!
double calculateRefractionAngle(const double theta_i,
                                const std::complex<double>& n_i,
                                const std::complex<double>& n_t);

//!
bool isPerfectReflection(const double theta_i,
                         const std::complex<double>& n_i,
                         const std::complex<double>& n_t);

//! \} Material

} // namespace reflect

#include "multilayer_thin_film_surface-inl.hpp"

#endif // _REFLECT_MULTILAYER_THIN_FILM_SURFACE_HPP_
