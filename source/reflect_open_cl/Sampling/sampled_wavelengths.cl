/*!
 \file sampled_wavelengths.cl
 \author takemura
 */

#include "reflect_config.h"
#include "sampled_wavelengths.h"
#include "sampler.h"
#include "spectral_distribution.h"

/*!
 \details
 No detailed.
 */
void copySampledWavelengths(const global SampledWavelengths* source,
                            local SampledWavelengths* destination)
{
  event_t event = async_work_group_copy(&destination->inverse_probabilities_, 
                                        &source->inverse_probabilities_, 
                                        1,
                                        0);
  event = async_work_group_copy(destination->wavelengths_, 
                                source->wavelengths_, 
                                kSpectraSampleSize, 
                                event);
  event = async_work_group_copy(&destination->primary_wavelength_index_,   
                                &source->primary_wavelength_index_, 
                                1, 
                                event);
  wait_group_events(3, &event);
}

#ifdef REFLECT_WAVELENGTH_STRATIFIED_SAMPLING

/*!
 \details
 No detailed.
 */
SampledWavelengths sampleWavelengths(SamplerState* sampler)
{
  SampledWavelengths wavelengths;
  for (size_t i = 0; i < kSpectraSampleSize; ++i) {
    const float position = kWavelengthInterval * ((float)i + sample(sampler));
    const size_t index = (size_t)(position);
    const ushort wavelength = getWavelength(index);
    wavelengths.wavelengths_[i] = wavelength;
    wavelengths.inverse_probabilities_[i] = kWavelengthInterval;
  }
  wavelengths.primary_wavelength_index_ = selectPrimaryWavelengthIndex(sampler);
  return wavelengths;
}

#endif

/*!
 \details
 No detailed.
 */
ushort selectPrimaryWavelengthIndex(SamplerState* sampler)
{
  const float position = (float)kSpectraSampleSize * sample(sampler);
  return (ushort)position;
}
