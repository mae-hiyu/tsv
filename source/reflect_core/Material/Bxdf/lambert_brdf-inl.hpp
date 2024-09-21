/*!
  \file lambert_brdf-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_LAMBERT_BRDF_INL_HPP_
#define _REFLECT_LAMBERT_BRDF_INL_HPP_

#include "lambert_brdf.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/size.hpp"


namespace reflect {

// Forward declaration
class SampledDirection;
class Sampler;
template <std::size_t> class WavelengthSamples;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
LambertBrdf<kSampleSize>::LambertBrdf(const Vector3& normal, 
                                      const Spectra& reflectance) :
    normal_{&normal},
    reflectance_{reflectance}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto LambertBrdf<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& /* wavelemgths */) const -> Spectra
{
  return reflectance_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto LambertBrdf<kSampleSize>::evaluateRadiance(
    const Vector3* /* vin */,
    const Vector3* /* vout */,
    const Wavelengths& /* wavelemgths */) const -> Spectra
{
  return k * reflectance_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t LambertBrdf<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(reflectance_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledDirection LambertBrdf<kSampleSize>::sampleDirection(Sampler& sampler) const
{
  return sampleDirectionOnHemisphere<1>(*normal_, sampler);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
bool LambertBrdf<kSampleSize>::wavelengthIsSelected() const
{
  return false;
}

} // namespace reflect

#endif // _REFLECT_LAMBERT_BRDF_INL_HPP_
