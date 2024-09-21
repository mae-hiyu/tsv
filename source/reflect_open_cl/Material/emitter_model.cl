/*!
 \file emitter_model.cl
 \author takemura
 */

#include "emitter_model.h"

#include "reflect_config.h"
#include "sampled_wavelengths.h"
#include "spectral_distribution.h"


/*! \brief Evaluate non-directional light radiance */
IntensitySamples evaluateNonDirectionalEmitterRadiance(
    const global EmitterModel* emitter, 
    const float3* vin, 
    const float3* normal, 
    const local SampledWavelengths* wavelengths);

const constant uchar kNonDirectionalEmitter = 0;

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateEmitterRadiance(
    const global EmitterModel* emitter,
    const float3* vin,
    const float3* normal,
    const local SampledWavelengths* wavelengths)
{
  IntensitySamples radiance;
  const uchar type = emitter->type_;
  switch (type) {
   case kNonDirectionalEmitter:
    radiance = 
        evaluateNonDirectionalEmitterRadiance(emitter, vin, normal, wavelengths);
    break;
   default:
    break;
  }
  return radiance;
}

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateNonDirectionalEmitterRadiance(
    const global EmitterModel* emitter, 
    const float3* vin, 
    const float3* normal, 
    const local SampledWavelengths* wavelengths)
{
  return makeSampleFromDistribution(&emitter->distribution_, wavelengths);
}
