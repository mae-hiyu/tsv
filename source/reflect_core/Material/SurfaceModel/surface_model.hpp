/*!
  \file surface_model.hpp
  \author takemura
  */

#ifndef _REFLECT_SURFACE_MODEL_HPP_
#define _REFLECT_SURFACE_MODEL_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "reflect_config.hpp"
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
enum class SurfaceType : int
{
  SmoothDiffuse = 0,
  SmoothDielectric,
  SmoothConductor,
  RoughDielectric,
  RoughConductor,
  MultilayerThinFilms,
};

/*!
  \details
  No detailed.
  */
class SurfaceModel
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = UniquePointer<ShaderModel<kSampleSize>>;


  virtual ~SurfaceModel() {}


  //! Make BxDF
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeBxdf(
      const Vector3* vin,
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the surface reflectance
  virtual SpectralDistribution reflectance() const;

  //! Return the surface type
  virtual SurfaceType type() const = 0;
};

//! Make a lambert BRDF
template <std::size_t kSampleSize>
SurfaceModel::ShaderPointer<kSampleSize> makeLambertBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool);

//! Make a lambert BRDF
template <std::size_t kSampleSize>
SurfaceModel::ShaderPointer<kSampleSize> makeSpecularBsdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool);

//! Make a lambert BRDF
template <std::size_t kSampleSize>
SurfaceModel::ShaderPointer<kSampleSize> makeSpecularBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool);

//! Make a lambert BRDF
template <std::size_t kSampleSize>
SurfaceModel::ShaderPointer<kSampleSize> makeThinFilmSpecularBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool);

//! Make a lambert BRDF
template <std::size_t kSampleSize>
SurfaceModel::ShaderPointer<kSampleSize> makeGgxConductorBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool);

//! Make a surface scattering model
UniquePointer<SurfaceModel> makeSurface(
    const QSettings& settings,
    const QString& prefix,
    const std::vector<const Texture*>& weight_list);

//! \} Material

} // namespace reflect

#include "surface_model-inl.hpp"

#endif // _REFLECT_SURFACE_MODEL_HPP_
