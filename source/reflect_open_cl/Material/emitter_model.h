/*!
 \file emitter_model.h
 \author takemura
 */

#ifndef _REFLECT_EMITTER_MODEL_H_
#define _REFLECT_EMITTER_MODEL_H_

#include "reflect_config.h"
#include "sampled_wavelengths.h"
#include "spectral_distribution.h"

/*!
 \details
 No detailed.
 */
typedef struct _EmitterModel
{
  SpectralDistribution distribution_;
  half radiant_emittance_;
  uchar type_;
} EmitterModel;

/*! \brief Evaluate the light radiance */
IntensitySamples evaluateEmitterRadiance(
    const global EmitterModel* emitter,
    const float3* vin,
    const float3* normal,
    const local SampledWavelengths* wavelengths);

#endif /* _REFLECT_EMITTER_MODEL_H_ */
