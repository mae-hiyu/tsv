/*!
  \file specular_bsdf-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECULAR_BSDF_INL_HPP_
#define _REFLECT_SPECULAR_BSDF_INL_HPP_

#include "specular_bsdf.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

// Forward declaration
class Sampler;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SpecularBsdf<kSampleSize>::SpecularBsdf(const Vector3& normal,
                                        const Vector3& vout,
                                        const double cos_theta_o,
                                        const double reflectance,
                                        const double transmittance) :
    normal_{&normal},
    vout_{vout},
    inverse_cos_theta_o_{1.0 / cos_theta_o},
    reflectance_{reflectance},
    transmittance_{transmittance}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto SpecularBsdf<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& wavelengths) const -> Spectra
{
  Spectra reflectance{wavelengths};
  const double weight = reflectance_ + transmittance_;
  reflectance.setIntensity(wavelengths.primaryWavelengthIndex(), weight);
  return reflectance;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto SpecularBsdf<kSampleSize>::evaluateRadiance(
    const Vector3* /* vin */,
    const Vector3* /* vout */,
    const Wavelengths& wavelengths) const -> Spectra
{
  Spectra reflectance{wavelengths};
//  reflectance.setIntensity(wavelengths.primaryWavelengthIndex(), 1.0 / cos_theta_o_);
  return reflectance;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t SpecularBsdf<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(vout_);
  size += PRINT_VARIABLE_DATA(inverse_cos_theta_o_);
  size += PRINT_VARIABLE_DATA(reflectance_);
  size += PRINT_VARIABLE_DATA(transmittance_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledDirection SpecularBsdf<kSampleSize>::sampleDirection(
    Sampler& /* sampler */) const
{
  return SampledDirection{vout_, 1.0};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
bool SpecularBsdf<kSampleSize>::wavelengthIsSelected() const
{
  return true;
}

} // namespace reflect

#endif // _REFLECT_SPECULAR_BSDF_INL_HPP_
