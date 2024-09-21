/*!
  \file non_directional_light-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_NON_DIRECTIONAL_LIGHT_INL_HPP_
#define _REFLECT_NON_DIRECTIONAL_LIGHT_INL_HPP_

#include "non_directional_light.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/size.hpp"

namespace reflect {

// Forward declaration
class Sampler;
template <std::size_t> class WavelengthSamples;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
NonDirectionalLight<kSampleSize>::NonDirectionalLight(
    const Vector3& normal,
    const Spectra& radiant_emittance) :
      normal_{&normal},
      radiant_emittance_{radiant_emittance}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto NonDirectionalLight<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& /* wavelengths */) const -> Spectra
{
  return radiant_emittance_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto NonDirectionalLight<kSampleSize>::evaluateRadiance(
    const Vector3* /* vin */,
    const Vector3* /* vout */,
    const Wavelengths& /* wavelengths */) const -> Spectra
{
  return k * radiant_emittance_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t NonDirectionalLight<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(radiant_emittance_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledDirection NonDirectionalLight<kSampleSize>::sampleDirection(Sampler& sampler)
    const
{
  return sampleDirectionOnHemisphere<1>(*normal_, sampler);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
bool NonDirectionalLight<kSampleSize>::wavelengthIsSelected() const
{
  return false;
}

} // namespace reflect

#endif // _REFLECT_NON_DIRECTIONAL_LIGHT_INL_HPP_
