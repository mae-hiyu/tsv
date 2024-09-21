/*!
  \file emitter_model-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_EMITTER_MODEL_INL_HPP_
#define _REFLECT_EMITTER_MODEL_INL_HPP_

#include "emitter_model.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "non_directional_emitter.hpp"
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Material/shader_model.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto EmitterModel::makeLight(const IntersectionInfo& intersection,
                             const WavelengthSamples<kSampleSize>& wavelengths,
                             Sampler& sampler,
                             MemoryPool& memory_pool) const 
    -> ShaderPointer<kSampleSize>
{
  ShaderPointer<kSampleSize> light;

  const auto emitter_type = type();
  switch (emitter_type) {
   case EmitterType::NonDirectional:
    light = makeNonDirectionalLight(this, intersection, wavelengths, sampler, memory_pool);
    break;
   default:
    zisc::raiseError("EmitterModelError: (type=", cast<int>(emitter_type),
                     ") makeLight method is not implemented.");
    break;
  }
  return light;
}

/*!
  \details
  No detailed.
  */
inline
const SpectralDistribution& EmitterModel::powerDistribution() const
{
  return power_distribution_;
}

/*!
  \details
  No detailed.
  */
inline
double EmitterModel::radiantEmittance() const
{
  return radiant_emittance_;
}

} // namespace reflect

#endif // _REFLECT_EMITTER_MODEL_INL_HPP_
