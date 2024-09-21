/*!
 \file bvh.cl
 \author takemura
 */

#include "bvh.h"

#include "bvh_node.h"
#include "intersection_point.h"
#include "object.h"
#include "reflect_config.h"
#include "ray.h"

/*!
 \details
 No detailed.
 */
IntersectionPoint findClosestIntersection(const Ray* ray,
                                          const global BvhNode* bvh,
                                          const global Object* object_list,
                                          const uint previous_object_index)
{
  IntersectionPoint intersection,
                    current_intersection;
  intersection.object_index_ = kNonObjectIndex;

  /* Set ray information */
  const float3 inverse_ray_dir = 1.0f / ray->direction_;
  const float3 ood = -ray->origin_ * inverse_ray_dir;
  uchar direction_sign[3];
  direction_sign[0] = (inverse_ray_dir.x < 0.0f) ? 1 : 0;
  direction_sign[1] = (inverse_ray_dir.y < 0.0f) ? 1 : 0;
  direction_sign[2] = (inverse_ray_dir.z < 0.0f) ? 1 : 0;

  size_t index = 0;
  float shortest_distance2 = FLT_MAX;
  while (true) {
    const BvhNode node = bvh[index];
    if (isIntersectedNode(&node, ray, &inverse_ray_dir, &ood, direction_sign)) {
      /* A case of leaf node */
      if (node.num_of_objects_ != 0) {
        for (size_t i = 0; i < node.num_of_objects_; ++i) {
          const uint object_index = node.object_index_list_[i];
          if (object_index == previous_object_index)
            continue;
          const Object object = object_list[object_index];
          if (isIntersectedObject(&object, ray, &current_intersection)) {
            const float3 d = current_intersection.point_ - ray->origin_;
            const float distance2 = dot(d, d);
            if (distance2 < shortest_distance2) {
              intersection = current_intersection;
              intersection.object_index_ = object_index;
              intersection.surface_scattering_index_ = 
                  object.surface_scattering_index_;
              intersection.emitter_index_ = object.emitter_index_;
              
              shortest_distance2 = distance2;
            }
          }
        }
      }
      /* A case of internal node */
      else {
        index = node.left_child_index_;
        continue;
      }
    }

    /* Back to the parent node until the current node is left node */
    while (!bvh[index].is_left_node_) {
      index = bvh[index].parent_index_;
      if (index == kNonObjectIndex)
        return intersection;
    }
    /* if the current node is left node, move to the right node */
    const uint parent_index = bvh[index].parent_index_;
    index = bvh[parent_index].right_child_index_;
  }
  /* Dummy */
  return intersection;
}
