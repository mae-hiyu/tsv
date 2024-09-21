/*!
  \file smooth_conductor_surface.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_CONDUCTOR_SURFACE_HPP_
#define _REFLECT_SMOOTH_CONDUCTOR_SURFACE_HPP_

// Standard C++ library
#include <cstddef>
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
class SmoothConductorSurface : public SurfaceModel 
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a smooth conductor surface
  SmoothConductorSurface(const QSettings& settings, const QString& prefix);


  //! Make a Fresnel BRDF
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeSpecularBrdf(
      const Vector3* vin,
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the smooth conductor surface type
  SurfaceType type() const override;

 private:
  //! Initialize
  void initialize(const QSettings& settings, const QString& prefix);


//  SpectralDistribution eta_, //!< The ratio of refractive index
//                       eta_k_; //!< Refractive index absorption ratio
  SpectralDistribution r0_;
};

//! \} Material

} // namespace reflect

#include "smooth_conductor_surface-inl.hpp"

#endif // _REFLECT_SMOOTH_CONDUCTOR_SURFACE_HPP_
