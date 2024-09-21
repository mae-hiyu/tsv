/*!
 \file sampled_spectra.cl
 \author takemura
 */

#include "sampled_spectra.h"

#include "reflect_config.h"

/*!
 \details
 No detailed.
 */
void fillSample(IntensitySamples* sample, const float value)
{
  *sample = (IntensitySamples)(value);
}

/*!
 \details
 No detailed.
 */
float maxSampleElement(const IntensitySamples* sample)
{
  float max_value = (*sample)[0];
  for (size_t index = 1; index < kSpectraSampleSize; ++index)
    max_value = max(max_value, (*sample)[index]);
  return max_value;
}
