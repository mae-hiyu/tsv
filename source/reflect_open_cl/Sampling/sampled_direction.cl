/*!
 \file sampled_direction.cl
 \author takemura
 */

#include "reflect_config.h"
#include "sampled_direction.h"
#include "sampler.h"
#include "vector.h"

/*!
 \details
 No detailed.
 */
float3 sampleCosineWeightedDirection(const float3* normal, SamplerState* sampler)
{
  const float phi = 2.0f * kPi * sample(sampler);
  const float cos_theta = sqrt(sample(sampler));
  const float sin_theta = sqrt(-fma(cos_theta, cos_theta, -1.0f));

  float3 direction = (float3)(sin_theta * cos(phi),
                              sin_theta * sin(phi),
                              cos_theta);

  changeBasisToNormal(normal, &direction);
  return direction;
}
