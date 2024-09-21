/*!
  \file ggx_conductor_brdf-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_GGX_CONDUCTOR_BRDF_INL_HPP_
#define _REFLECT_GGX_CONDUCTOR_BRDF_INL_HPP_

#include "ggx_conductor_brdf.hpp"
// Sstandard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
GgxConductorBrdf<kSampleSize>::GgxConductorBrdf(const double roughness,
                                                const Vector3& normal,
                                                const Spectra& r0,
                                                const SampledDirection& vout,
                                                const Spectra& weight) :
    r0_{r0},
    weight_{weight},
    vout_{vout},
    roughness_{roughness},
    normal_{&normal}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto GgxConductorBrdf<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& /* wavelengths */) const -> Spectra
{
  return weight_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto GgxConductorBrdf<kSampleSize>::evaluateRadiance(
    const Vector3* vin,
    const Vector3* vout,
    const Wavelengths& /* wavelengths */) const -> Spectra
{
  const double cos_theta_i = -zisc::dot(*normal_, *vin);
  const double cos_theta_o = zisc::dot(*normal_, *vout);
  const auto f = evaluateGgxReflectance(roughness_, *vin, *vout, *normal_, r0_,
                                        cos_theta_i, cos_theta_o);
  REFLECT_CHECK_POSITIVE_FLOAT(f);

  return f;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t GgxConductorBrdf<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(r0_);
  size += PRINT_VARIABLE_DATA(weight_);
  size += PRINT_VARIABLE_DATA(vout_);
  size += PRINT_VARIABLE_DATA(roughness_);
  size += PRINT_VARIABLE_DATA(normal_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledDirection GgxConductorBrdf<kSampleSize>::sampleDirection(
    Sampler& /* sampler */) const
{
  return vout_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
bool GgxConductorBrdf<kSampleSize>::wavelengthIsSelected() const
{
  return false;
}

} // namespace reflect

#endif // _REFLECT_GGX_CONDUCTOR_BRDF_INL_HPP_
