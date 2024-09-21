/*!
 \file weight.h
 \author takemura
 */

#ifndef _REFLECT_WEIGHT_H_
#define _REFLECT_WEIGHT_H_

#include "sampled_wavelengths.h"
#include "spectral_distribution.h"

/*!
 \details
 No detailed.
 */
typedef struct _Weight
{
  uint index_;
  ushort parameter_[2];
  uchar type_;
} Weight;

/*! \brief Evaluate spectra weight */
IntensitySamples evaluateSpectraWeight(
    const global Weight* weight,
    const global uint* weight_color_index_array,
    const global SpectralDistribution* weight_spectra_array,
    const local SampledWavelengths* wavelengths);

#endif /* _REFLECT_WEIGHT_H_ */
