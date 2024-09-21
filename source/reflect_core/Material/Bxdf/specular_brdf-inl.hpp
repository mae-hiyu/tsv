/*!
  \file specular_brdf-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECULAR_BRDF_INL_HPP_
#define _REFLECT_SPECULAR_BRDF_INL_HPP_

#include "specular_brdf.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Material/SurfaceModel/fresnel.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SpecularBrdf<kSampleSize>::SpecularBrdf(const Vector3& normal,
                                        const Vector3& vout,
                                        const double cos_theta_o,
                                        const Spectra& reflectance) :
    reflectance_{reflectance},
    normal_{&normal},
    vout_{vout},
    inverse_cos_theta_o_{1.0 / cos_theta_o}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto SpecularBrdf<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& /* wavelengths */) const -> Spectra
{
  return reflectance_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto SpecularBrdf<kSampleSize>::evaluateRadiance(
    const Vector3* /* vin */,
    const Vector3* /* vout */,
    const Wavelengths& /* wavelengths */) const -> Spectra
{
  return reflectance_ * inverse_cos_theta_o_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t SpecularBrdf<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(reflectance_);
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(vout_);
  size += PRINT_VARIABLE_DATA(inverse_cos_theta_o_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledDirection SpecularBrdf<kSampleSize>::sampleDirection(
    Sampler& /* sampler */) const
{
  return SampledDirection{vout_, 1.0};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
bool SpecularBrdf<kSampleSize>::wavelengthIsSelected() const
{
  return false;
}

} // namespace reflect

#endif // _REFLECT_SPECULAR_BRDF_INL_HPP_
