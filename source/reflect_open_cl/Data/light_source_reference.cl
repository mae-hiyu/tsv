/*!
 \file light_source_reference
 \author takemura
 */

#include "light_source_reference.h"

#include "reflect_config.h"
#include "sampler.h"

/*! \brief Select right source */
uint selectLightSource(const global LightSourceReference* light_source_list,
                       float* inverse_probability,
                       SamplerState* sampler)
{
  const float threshold = sample(sampler);
  float sum = 0.0f;
  for (size_t index = 0; index < kNumOfLightSources; ++index) {
    const global LightSourceReference* light = &light_source_list[index];
    const float weight = vload_half(0, &light->weight_);
    sum += weight;
    if (threshold < sum) {
      *inverse_probability = 1.0f / weight;
      return light->object_index_;
    }
  }
  return 0;
}
