/*!
  \file smooth_dielectric_surface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTH_DIELECTRIC_SURFACE_INL_HPP_
#define _REFLECT_SMOOTH_DIELECTRIC_SURFACE_INL_HPP_

#include "smooth_dielectric_surface.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "fresnel.hpp"
#include "Data/intersection_info.hpp"
#include "Data/wavelength_samples.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Material/Bxdf/specular_bsdf.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto SmoothDielectricSurface::makeSpecularBsdf(
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Bsdf = SpecularBsdf<kSampleSize>;
 
  const auto wavelength = wavelengths[wavelengths.primaryWavelengthIndex()];
  const double n = intersection.isReverseFace()
      ? 1.0 / eta_.getByWavelength(wavelength)
      : eta_.getByWavelength(wavelength);

  const auto& normal = intersection.normal();
  const double cos_theta_i = -zisc::dot(normal, *vin);
  REFLECT_CHECK_NON_ZERO_FLOAT(cos_theta_i);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_i);

  const auto g = evaluateFresnelG(n, cos_theta_i);
  const double reflectance = (g.first)
      ? solveFresnelDielectricEquation(cos_theta_i, g.second)
      : 1.0; // Perfect reflection
  const bool is_reflection = (sampler.sample(0.0, 1.0) < reflectance);
  const auto vout = is_reflection
      ? getFresnelReflectionDirection(*vin, normal, cos_theta_i)
      : getFresnelRefractionDirection(*vin, normal, cos_theta_i, n, g.second);
  const double cos_theta_o = is_reflection ? cos_theta_i : g.second / n;
  REFLECT_CHECK_NON_ZERO_FLOAT(cos_theta_o);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_o);

  auto bsdf = memory_pool.allocate<Bsdf>(normal, 
                                         vout, 
                                         cos_theta_o, 
                                         reflectance, 
                                         1.0 - reflectance);
  return ShaderPointer<kSampleSize>{bsdf};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SurfaceModel::ShaderPointer<kSampleSize> makeSpecularBsdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto dielectric_surface = cast<const SmoothDielectricSurface*>(surface);
  return dielectric_surface->makeSpecularBsdf(vin,
                                              intersection,
                                              wavelengths,
                                              sampler,
                                              memory_pool);
}

} // namespace reflect

#endif // _REFLECT_SMOOTH_DIELECTRIC_SURFACE_INL_HPP_
