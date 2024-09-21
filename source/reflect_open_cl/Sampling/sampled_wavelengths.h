/*!
 \file sampled_wavelengths.h
 \author takemura
 */

#ifndef _REFLECT_SAMPLED_WAVELENGTHS_H_
#define _REFLECT_SAMPLED_WAVELENGTHS_H_

#include "reflect_config.h"
#include "sampler.h"

/*!
 \details
 No detailed.
 */
typedef struct _SampledWavelengths
{
  IntensitySamples inverse_probabilities_;
  ushort wavelengths_[kSpectraSampleSize];
  ushort primary_wavelength_index_;
} SampledWavelengths;

/*! \brief Copy wavelength sample */
void copySampledWavelengths(const global SampledWavelengths* source,
                            local SampledWavelengths* destination);

/*! \brief Sample wavelengths */
SampledWavelengths sampleWavelengths(SamplerState* sampler);

/*! \brief select primary wavelength index */
ushort selectPrimaryWavelengthIndex(SamplerState* sampler);

#endif /* _REFLECT_SAMPLED_WAVELENGTHS_H_ */
