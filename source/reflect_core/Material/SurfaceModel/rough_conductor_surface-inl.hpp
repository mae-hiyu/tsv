/*!
  \file rough_conductor_surface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_ROUGH_CONDUCTOR_SURFACE_INL_HPP_
#define _REFLECT_ROUGH_CONDUCTOR_SURFACE_INL_HPP_

#include "rough_conductor_surface.hpp"
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
#include "Material/Bxdf/ggx_conductor_brdf.hpp"
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
auto RoughConductorSurface::makeGgxConductorBrdf(
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Brdf = GgxConductorBrdf<kSampleSize>;

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
  const auto r0 = sample(r0_, wavelengths);
  const auto fresnel = solveFresnelConductorEquation(cos_theta_mi, r0);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(fresnel);

  // Reflection direction
  auto vout = getMicrofacetReflectionDirection(*vin, m_normal, cos_theta_mi);
  const double cos_theta_o = zisc::dot(normal, vout.direction());
//  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_o);
  //! todo: Is it correct operation ?
  if (cos_theta_o < 0.0) {
    SampledSpectra<kSampleSize> weight{wavelengths};
    auto brdf = memory_pool.allocate<Brdf>(alpha, normal, r0, vout, weight);
    vout.setInversePdf(0.0);
    return ShaderPointer<kSampleSize>{brdf};
  }

  // Evaluate weight
  const double cos_theta_mo = cos_theta_mi;
  const auto weight = fresnel *
                      evaluateGgxWeight(alpha, cos_theta_i, cos_theta_o,
                                        cos_theta_m, cos_theta_mi, cos_theta_mo);

  // Make GGX BRDF
  auto brdf = memory_pool.allocate<Brdf>(alpha, normal, r0, vout, weight);
  return ShaderPointer<kSampleSize>{brdf};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SurfaceModel::ShaderPointer<kSampleSize> makeGgxConductorBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto conductor_surface = cast<const RoughConductorSurface*>(surface);
  return conductor_surface->makeGgxConductorBrdf(vin,
                                                 intersection,
                                                 wavelengths,
                                                 sampler,
                                                 memory_pool);
}

} // namespace reflect

#endif // _REFLECT_ROUGH_CONDUCTOR_SURFACE_INL_HPP_
