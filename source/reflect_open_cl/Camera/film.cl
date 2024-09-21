/*!
 \file film.cl
 \author takemura
 */

#include "film.h"

#include "reflect_config.h"
#include "sampler.h"

const constant float inverse_width = 1.0f / (float)kWidthResolution;
const constant float inverse_height = 1.0f / (float)kHeightResolution;

/*!
 \details
 No detailed.
 */
float2 sampleFilmCoordinate(const size_t pixel_index, SamplerState* sampler)
{
  const size_t y = pixel_index / kWidthResolution;
  const size_t x = pixel_index - (y * kWidthResolution);
#ifdef REFLECT_JITTERING
  const float delta_x = sample(sampler);
  const float delta_y = sample(sampler);
#else /* REFLECT_JITTERING */
  const float delta_x = 0.5f;
  const float delta_y = 0.5f;
#endif /* REFLECT_JITTERING */
  return (float2)(((float)x + delta_x) * inverse_width,
                  ((float)y + delta_y) * inverse_height);
}
