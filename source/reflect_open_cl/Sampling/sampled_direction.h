/*!
 \file sampled_direction.h
 \author takemura
 */

#ifndef _REFLECT_SAMPLED_DIRECTION_H_
#define _REFLECT_SAMPLED_DIRECTION_H_

#include "sampler.h"

/*! \brief Sample direction according the pdf p(w) = cos(theta) / pi */
float3 sampleCosineWeightedDirection(const float3* normal, SamplerState* sampler);

#endif /* _REFLECT_SAMPLED_DIRECTION_H_ */
