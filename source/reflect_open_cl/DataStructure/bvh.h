/*!
 \file bvh.h
 \author takemura
 */

#ifndef _REFLECT_BVH_H_
#define _REFLECT_BVH_H_

#include "bvh_node.h"
#include "intersection_point.h"
#include "object.h"
#include "ray.h"

/*! \brief Find closest intersection object */
IntersectionPoint findClosestIntersection(const Ray* ray, 
                                          const global BvhNode* bvh,
                                          const global Object* object_list,
                                          const uint previous_object_index);

#endif /* _REFLECT_BVH_H_ */
