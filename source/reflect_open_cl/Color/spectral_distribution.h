/*!
 \file spectral_distribution.h
 \author takemura
 */

#ifndef _REFLECT_SPECTRAL_DISTRIBUTION_H_
#define _REFLECT_SPECTRAL_DISTRIBUTION_H_

#include "reflect_config.h"
#include "sampled_wavelengths.h"

/*!
 \details
 No detailed.
 */
typedef struct _SpectralDistribution
{
  half distribution_[kSpectraSize];
} SpectralDistribution;

/*! \brief Add radiance to buffer */
void addRadiance(const size_t pixel_index,
                 const IntensitySamples* radiance,
                 const local SampledWavelengths* wavelengths,
                 global SpectralDistribution* spectra_buffer);

/*! \brief Get index from the wavelength */
size_t getIndex(const ushort wavelength);

/*! \brief Get wavelength from the index */
ushort getWavelength(const size_t index);

/*! \brief Make sampled spectra from distribution */
IntensitySamples makeSampleFromDistribution(
    const global SpectralDistribution* distribution,
    const local SampledWavelengths* wavelengths);

#endif /* _REFLECT_SPECTRAL_DISTRIBUTION_H_ */
