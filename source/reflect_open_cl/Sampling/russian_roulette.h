/*!
 \file russian_roulette.h
 \author takemura
 */

#ifndef _REFLECT_RUSSIAN_ROULETTE_H_
#define _REFLECT_RUSSIAN_ROULETTE_H_

#include "reflect_config.h"
#include "sampler.h"

/*!
 \details
 No detailed.
 */
typedef struct _RouletteResult
{
  float probability_;
  bool result_;
} RouletteResult;

/*! \brief Russian roulette */
RouletteResult playRussianRoulette(const size_t path,
                                   const IntensitySamples* weight,
                                   SamplerState* sampler);

#endif /* _REFLECT_RUSSIAN_ROULETTE_H_ */
