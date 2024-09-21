/*!
 \file sampled_spectra.h
 \author takemura
 */

#ifndef _REFLECT_SAMPLED_SPECTRA_H_
#define _REFLECT_SAMPLED_SPECTRA_H_

#include "reflect_config.h"

/*! \brief fill sample elements by value */
void fillSample(IntensitySamples* sample, const float value);

/*! \brief Return the max element of the sample */
float maxSampleElement(const IntensitySamples* sample);

#endif /* _REFLECT_SAMPLED_SPECTRA_H_ */
