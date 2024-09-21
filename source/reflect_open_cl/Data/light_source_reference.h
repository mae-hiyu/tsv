/*!
 \file light_source_reference.h
 \author takemura
 */

#ifndef _REFLECT_LIGHT_SOURCE_REFERENCE_H_
#define _REFLECT_LIGHT_SOURCE_REFERENCE_H_

#include "sampler.h"

/*!
 \details
 No detailed.
 */
typedef struct _LightSourceReference
{
  uint object_index_;
  half weight_,
       inverse_weight_;
} LightSourceReference;

/*! \brief Select right source */
uint selectLightSource(const global LightSourceReference* light_source_list,
                       float* inverse_probability,
                       SamplerState* sampler);

#endif /* _REFLECT_LIGHT_SOURCE_REFERENCE_H_ */
