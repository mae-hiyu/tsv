/*!
 \file spectral_distribution.cl
 \author takemura
 */

#include "spectral_distribution.h"

#include "reflect_config.h"
#include "sampled_spectra.h"
#include "sampled_wavelengths.h"

/*!
 \details
 No detailed.
 */
void addRadiance(const size_t pixel_index,
                 const IntensitySamples* radiance,
                 const local SampledWavelengths* wavelengths,
                 global SpectralDistribution* spectra_buffer)
{
  const size_t number = pixel_index - kDevicePixelSize * get_global_offset(0);
  global SpectralDistribution* buffer = &spectra_buffer[number];
  for (size_t index = 0; index < kSpectraSampleSize; ++index) {
    const ushort wavelength = wavelengths->wavelengths_[index];
    const size_t i = getIndex(wavelength);
    const float r = vload_half(i, buffer->distribution_);
    vstore_half(r + (*radiance)[index], i, buffer->distribution_);
  }
}

/*! \brief Get index from the wavelength */
size_t getIndex(const ushort wavelength)
{
  return (size_t)((wavelength - kShortestWavelength) / kWavelengthResolution);
}

/*! \brief Get wavelength from the index */
ushort getWavelength(const size_t index)
{
  return kShortestWavelength + (ushort)index * kWavelengthResolution;
}

/*!
 \details
 No detailed.
 */
IntensitySamples makeSampleFromDistribution(
    const global SpectralDistribution* distribution,
    const local SampledWavelengths* wavelengths)
{
  IntensitySamples sample;
  for (size_t index = 0; index < kSpectraSampleSize; ++index) {
    const size_t wavelength = wavelengths->wavelengths_[index];
    const size_t i = getIndex(wavelength);
    sample[index] = vload_half(i, distribution->distribution_);
  }
  return sample;
}
