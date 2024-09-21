/*!
 \file weight.cl
 \author takemura
 */

#include "weight.h"

#include "sampled_wavelengths.h"
#include "spectral_distribution.h"

/*! \brief Evaluate unicolor spectra weight */
IntensitySamples evaluateUnicolorSpectraWeight(
    const Weight* weight,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths);

const constant uchar kValueWeight = 0;
const constant uchar kUnicolorWeight = 1;

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateSpectraWeight(
    const global Weight* weight,
    const global uint* weight_color_index_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths)
{
  IntensitySamples spectra_weight;
  const Weight w = *weight;
  switch (w.type_) {
   case kUnicolorWeight:
    spectra_weight = 
        evaluateUnicolorSpectraWeight(&w, weight_spectra_array, wavelengths);
    break;
   default:
    break;
  }
  return spectra_weight;
}

/*!
 \details
 No detailed.
 */
IntensitySamples evaluateUnicolorSpectraWeight(
    const Weight* weight,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths)
{
  const global SpectralDistribution* spectra_array = 
      &weight_spectra_array[weight->index_];
  return makeSampleFromDistribution(spectra_array, wavelengths);
}
