/*!
 \file object.h
 \author takemura
 */

#ifndef _REFLECT_OBJECT_H_
#define _REFLECT_OBJECT_H_

#include "intersection_point.h"
#include "ray.h"
#include "sampler.h"

/*!
 \details
 No detailed.
 */
typedef struct _Object
{
  float3 axis_[3];
  float3 point_;
  ushort surface_scattering_index_;
  ushort emitter_index_;
  half area_;
  uchar type_;
} Object;

/*! \brief Test ray object intersection */
bool isIntersectedObject(const Object* object,
                         const Ray* ray,
                         IntersectionPoint* intersection);

/*! \brief sample a point on the object */
float3 sampleObjectPoint(const Object* object, 
                         float* inverse_probability,
                         SamplerState* sampler);

/*! \brief sample a point on the object using importance sampling*/
float3 sampleObjectPointImportance(const Object* object,
                                   const IntersectionPoint* intersection,
                                   float* inverse_probability,
                                   SamplerState* sampler);

#endif /* _REFLECT_OBJECT_H_ */
