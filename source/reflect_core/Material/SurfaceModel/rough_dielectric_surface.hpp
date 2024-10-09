/*!
  \file rough_dielectric_surface.hpp
  \author takemura
  */

#ifndef _REFLECT_ROUGH_DIELECTRIC_SURFACE_HPP_
#define _REFLECT_ROUGH_DIELECTRIC_SURFACE_HPP_

// Standard C++ library
#include <cstddef>
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
template <std::size_t> class ShaderModel;
class Texture;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
class RoughDielectricSurface : public SurfaceModel
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a rough dielectric surface
  RoughDielectricSurface(const QSettings& settings, 
                         const QString& prefix,
                         const std::vector<const Texture*>& texture_list);


  //! Make a GGX BSDF
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeGgxDielectricBsdf(
      const Vector3* vin,
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the rough dielectric surface type
  SurfaceType type() const override;

 private:
  //! Initialize
  void initialize(const QSettings& settings,
                  const QString& prefix,
                  const std::vector<const Texture*>& texture_list);
  

  const Texture* roughness_;
  SpectralDistribution eta_;
};

//! \} Material

} // namespace reflect

#include "rough_dielectric_surface-inl.hpp"

#endif // _REFLECT_ROUGH_DIELECTRIC_SURFACE_HPP_