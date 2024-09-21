/*!
 \file bvh_node.h
 \author takemura
 */

#ifndef _REFLECT_BVH_NODE_H_
#define _REFLECT_BVH_NODE_H_

#include "aabb.h"
#include "ray.h"
#include "reflect_config.h"

/*!
 \details
 No detailed.
 */
typedef struct _BvhNode
{
  Aabb bounding_box_;
  uint object_index_list_[kMaxNodeObjects];
  uint parent_index_,
       left_child_index_,
       right_child_index_;
  ushort num_of_objects_;
  uchar is_left_node_;
} BvhNode;

/*! \brief Test ray node intersection */
bool isIntersectedNode(const BvhNode* node, 
                       const Ray* ray, 
                       const float3* inverse_ray_dir,
                       const float3* ood,
                       const uchar* direction_sign);

#endif /* _REFLECT_BVH_NODE_H_ */
