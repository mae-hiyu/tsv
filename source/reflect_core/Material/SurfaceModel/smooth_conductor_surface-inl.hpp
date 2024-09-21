/*!
  \file smooth_conductor_surface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_CONDUCTOR_SURFACE_INL_HPP_
#define _REFLECT_SMOOTH_CONDUCTOR_SURFACE_INL_HPP_

#include "smooth_conductor_surface.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "fresnel.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/intersection_info.hpp"
#include "Data/wavelength_samples.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Material/Bxdf/specular_brdf.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SmoothConductorSurface::makeSpecularBrdf(
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& /* sampler */,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Brdf = SpecularBrdf<kSampleSize>;

  const auto& normal = intersection.normal();
  const auto cos_theta_i = -zisc::dot(normal, *vin);
  REFLECT_CHECK_NON_ZERO_FLOAT(cos_theta_i);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_i);

  const auto vout = getFresnelReflectionDirection(*vin, normal, cos_theta_i);

  const auto r0 = sample(r0_, wavelengths);
  const auto reflectance = solveFresnelConductorEquation(cos_theta_i, r0);

  auto brdf = memory_pool.allocate<Brdf>(normal, vout, cos_theta_i, reflectance);
  return ShaderPointer<kSampleSize>{brdf};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SurfaceModel::ShaderPointer<kSampleSize> makeSpecularBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto conductor_surface = cast<const SmoothConductorSurface*>(surface);
  return conductor_surface->makeSpecularBrdf(vin,
                                             intersection,
                                             wavelengths,
                                             sampler,
                                             memory_pool);
}

} // namespace reflect

#endif // _REFLECT_SMOOTH_CONDUCTOR_SURFACE_INL_HPP_
