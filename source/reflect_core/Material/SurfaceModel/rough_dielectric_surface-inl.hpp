/*!
  \file rough_dielectric_surface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_ROUGH_DIELECTRIC_SURFACE_INL_HPP_
#define _REFLECT_ROUGH_DIELECTRIC_SURFACE_INL_HPP_

#include "rough_dielectric_surface.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "fresnel.hpp"
#include "microfacet.hpp"
#include "microfacet_ggx.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/intersection_info.hpp"
#include "Data/wavelength_samples.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Material/Bxdf/ggx_dielectric_bsdf.hpp"
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
template <std::size_t kSampleSize>
auto RoughDielectricSurface::makeGgxDielectricBsdf(
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Bsdf = GgxDielectricBsdf<kSampleSize>;

  const auto wavelength = wavelengths[wavelengths.primaryWavelengthIndex()];

  // Sample microfacet normal
  const auto& normal = intersection.normal();
  const double roughness = roughness_->floatValue(intersection.textureCoordinate());
  const double alpha = roughness * roughness;
  double cos_theta_i = 0.0,
         cos_theta_m = 0.0,
         cos_theta_mi = 0.0;
  const auto m_normal = sampleGgxMicrofacetNormal(alpha, *vin, normal, sampler,
                                                  &cos_theta_i, &cos_theta_m, &cos_theta_mi);

  // Evaluate fresnel term
  const double n = intersection.isReverseFace()
      ? 1.0 / eta_.getByWavelength(wavelength)
      : eta_.getByWavelength(wavelength);
  const auto g = evaluateFresnelG(n, cos_theta_mi);
  const double reflectance = (g.first)
      ? solveFresnelDielectricEquation(cos_theta_mi, g.second)
      : 1.0; // Perfect reflection

  // Calculate reflection direction
  const bool is_reflection = (sampler.sample(0.0, 1.0) < reflectance);
  double cos_theta_mo = cos_theta_mi;
  const auto vout = is_reflection
      ? getMicrofacetReflectionDirection(*vin, m_normal, cos_theta_mi)
      : getMicrofacetRefractionDirection(*vin, m_normal, cos_theta_mi, 
                                         n, g.second, &cos_theta_mo);

  // Evaluate weight
  const double cos_theta_o = zisc::dot(normal, vout.direction());
  const double weight = evaluateGgxWeight(alpha, cos_theta_i, cos_theta_o, 
                                          cos_theta_m, cos_theta_mi, cos_theta_mo);

  // Make GGX BSDF
  auto bsdf = memory_pool.allocate<Bsdf>(alpha, normal, n, vout, weight);
  return ShaderPointer<kSampleSize>(bsdf);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SurfaceModel::ShaderPointer<kSampleSize> makeGgxDielectricBsdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto dielectric_surface = cast<const RoughDielectricSurface*>(surface);
  return dielectric_surface->makeGgxDielectricBsdf(vin,
                                                   intersection,
                                                   wavelengths,
                                                   sampler,
                                                   memory_pool);
}

} // namespace reflect

#endif // _REFLECT_ROUGH_DIELECTRIC_SURFACE_INL_HPP_
