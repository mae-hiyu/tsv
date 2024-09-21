/*!
  \file smooth_diffuse_surface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_DIFFUSE_SURFACE_INL_HPP_
#define _REFLECT_SMOOTH_DIFFUSE_SURFACE_INL_HPP_

#include "smooth_diffuse_surface.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "Data/intersection_info.hpp"
#include "Data/wavelength_samples.hpp"
#include "Material/shader_model.hpp"
#include "Material/Bxdf/lambert_brdf.hpp"
#include "Material/Texture/texture.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

using zisc::cast;
  
/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SmoothDiffuseSurface::makeLambertBrdf(
    const Vector3* /* vin */,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& /* sampler */,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Brdf = LambertBrdf<kSampleSize>;

  const auto reflectance = 
      reflectance_->spectraValue(intersection.textureCoordinate(), wavelengths);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(reflectance);

  const auto& normal = intersection.normal();

  auto brdf = memory_pool.allocate<Brdf>(normal, reflectance);
  return ShaderPointer<kSampleSize>{brdf};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SurfaceModel::ShaderPointer<kSampleSize> makeLambertBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto diffuse_surface = cast<const SmoothDiffuseSurface*>(surface);
  return diffuse_surface->makeLambertBrdf(vin, 
                                          intersection, 
                                          wavelengths, 
                                          sampler, 
                                          memory_pool);
}

} // namespace reflect

#endif // _REFLECT_SMOOTH_DIFFUSE_SURFACE_INL_HPP_
