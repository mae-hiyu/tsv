/*!
 \file russian_roulette.cl
 \author takemura
 */

#include "russian_roulette.h"

#include "reflect_config.h"
#include "sampled_spectra.h"
#include "sampler.h"

#ifdef REFLECT_RUSSIAN_ROULETTE_PATH_LENGTH

#elif REFLECT_RUSSIAN_ROULETTE_AVERAGE

#elif REFLECT_RUSSIAN_ROULETTE_MAX

/*!
 \details
 No detailed.
 */
RouletteResult playRussianRoulette(const size_t path,
                                   const IntensitySamples* weight,
                                   SamplerState* sampler)
{
  RouletteResult result;
  const float max_value = maxSampleElement(weight);
  result.probability_ = (max_value > 1.0f) ? 1.0f : max_value;
  result.result_ = sample(sampler) < result.probability_;
  return result;
}

#endif
