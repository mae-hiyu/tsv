/*!
  \file smooth_diffuse_surface.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_DIFFUSE_SURFACE_HPP_
#define _REFLECT_SMOOTH_DIFFUSE_SURFACE_HPP_

// Standard C++ library
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "surface_model.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class IntersectionInfo;
class Sampler;
template <std::size_t> class ShaderModel;
class SpectralDistribution;
class Texture;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
class SmoothDiffuseSurface : public SurfaceModel
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a smooth diffuse surface
  SmoothDiffuseSurface(const QSettings& settings, 
                       const QString& prefix,
                       const std::vector<const Texture*>& texture_list);


  //! Make Lambert BRDF
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeLambertBrdf(
      const Vector3* vin,
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the diffuse surface reflectance
  SpectralDistribution reflectance() const override;

  //! Return the diffuse surface type
  SurfaceType type() const override;

 private:
  //! Initialize
  void initialize(const QSettings& settings, 
                  const QString& prefix,
                  const std::vector<const Texture*>& texture_list);


  const Texture* reflectance_;
};

//! \} Material

} // namespace reflect

#include "smooth_diffuse_surface-inl.hpp"

#endif // _REFLECT_SMOOTH_DIFFUSE_SURFACE_HPP_
