/*!
 \file ray.h
 \author takemura
 */

#ifndef _REFLECT_RAY_H_
#define _REFLECT_RAY_H_

#include "reflect_config.h"

/*!
 \details
 No detailed.
 */
typedef struct _Ray
{
  IntensitySamples weight_;
  float3 origin_,
         direction_;
} Ray;

#endif /* _REFLECT_RAY_H_ */
