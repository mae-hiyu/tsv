/*!
 \file intersection_point.h
 \author takemura
 */

#ifndef _REFLECT_INTERSECTION_POINT_H_
#define _REFLECT_INTERSECTION_POINT_H_

/*!
 \details
 No detailed.
 */
typedef struct _IntersectionPoint
{
  float3 normal_;
  float3 point_;
  float2 texture_coordinate_;
  uint object_index_;
  ushort surface_scattering_index_;
  ushort emitter_index_;
  bool is_reverse_face_;
} IntersectionPoint;

#endif /* _REFLECT_INTERSECTION_POINT_H_ */
