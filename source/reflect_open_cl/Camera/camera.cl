/*!
 \file camera.cl
 \author takemura
 */

#include "camera.h"

#include "film.h"
#include "ray.h"
#include "reflect_config.h"
#include "sampled_spectra.h"
#include "sampler.h"

#ifdef REFLECT_PINHOLE_CAMERA

const constant float3 position = (float3)(REFLECT_PINHOLE_POSITION_X,
                                          REFLECT_PINHOLE_POSITION_Y,
                                          REFLECT_PINHOLE_POSITION_Z);
const constant float3 film_position = (float3)(REFLECT_FILM_POSITION_X,
                                               REFLECT_FILM_POSITION_Y,
                                               REFLECT_FILM_POSITION_Z);
const constant float3 film_axis1 = (float3)(REFLECT_FILM_AXIS1_X,
                                            REFLECT_FILM_AXIS1_Y,
                                            REFLECT_FILM_AXIS1_Z);
const constant float3 film_axis2 = (float3)(REFLECT_FILM_AXIS2_X,
                                            REFLECT_FILM_AXIS2_Y,
                                            REFLECT_FILM_AXIS2_Z);

/*!
 \details
 No detailed.
 */
Ray generateRay(const size_t pixel_index, SamplerState* sampler)
{
  const float2 coordinate = sampleFilmCoordinate(pixel_index, sampler);
  const float3 tmp = fma(film_axis1, coordinate.x, film_position);
  const float3 pixel_point = fma(film_axis2, coordinate.y, tmp);
  const float3 direction = normalize(pixel_point - position);
  /* \todo Make from response function */
  IntensitySamples weight = (IntensitySamples)1.0f;

  Ray ray = {weight, position, direction};
  return ray;
}

#endif
