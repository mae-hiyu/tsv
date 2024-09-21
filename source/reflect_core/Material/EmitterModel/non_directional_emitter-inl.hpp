/*!
  \file non_directional_light-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_NON_DIRECTIONA_LIGHT_INL_HPP_
#define _REFLECT_NON_DIRECTIONA_LIGHT_INL_HPP_

#include "non_directional_emitter.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "emitter_model.hpp"
#include "reflect_config.hpp"
#include "Data/intersection_info.hpp"
#include "Material/shader_model.hpp"
#include "Material/Light/non_directional_light.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto NonDirectionalEmitter::makeNonDirectionalLight(
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& /* sampler */,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Light = NonDirectionalLight<kSampleSize>;

  const auto& normal = intersection.normal();
  const auto radiant_emittance = sample(powerDistribution(), wavelengths);

  auto light = memory_pool.allocate<Light>(normal, radiant_emittance);
  return ShaderPointer<kSampleSize>{light};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
EmitterModel::ShaderPointer<kSampleSize> makeNonDirectionalLight(
    const EmitterModel* emitter,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto non_directional_emitter = cast<const NonDirectionalEmitter*>(emitter);
  return non_directional_emitter->makeNonDirectionalLight(intersection,
                                                          wavelengths,
                                                          sampler,
                                                          memory_pool);
}

} // namespace reflect

#endif // _REFLECT_NON_DIRECTIONA_LIGHT_INL_HPP_
