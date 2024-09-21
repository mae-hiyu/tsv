/*!
  \file smooth_dielectric_surface.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_DIELECTRIC_SURFACE_HPP_
#define _REFLECT_SMOOTH_DIELECTRIC_SURFACE_HPP_

// Standard C++ library
#include <vector>
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
class SmoothDielectricSurface : public SurfaceModel
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a smooth dielectric surface
  SmoothDielectricSurface(const QSettings& settings, const QString& prefix);


  //! Make a Fresnel BRDF
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeSpecularBsdf(
      const Vector3* vin,
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the diffuse surface type
  SurfaceType type() const override;

 private:
  //! Initialize
  void initialize(const QSettings& settings, const QString& prefix);


  SpectralDistribution eta_; //!< Interior exteriro ratio of refractive index
};

//! \} Material

} // namespace reflect

#include "smooth_dielectric_surface-inl.hpp"

#endif // _REFLECT_SMOOTH_DIELECTRIC_SURFACE_HPP_
