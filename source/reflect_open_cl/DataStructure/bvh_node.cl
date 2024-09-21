/*!
 \file bvh_node.cl
 \author takemura
 */

#include "aabb.h"
#include "bvh_node.h"
#include "ray.h"

/*!
 \details
 No detailed.
 */
bool isIntersectedNode(const BvhNode* node,
                       const Ray* ray,
                       const float3* inverse_ray_dir,
                       const float3* ood,
                       const uchar* direction_sign)
{
  const Aabb* box = &node->bounding_box_;
  const float3 min_point = (float3)(box->point_[direction_sign[0]].x,
                                    box->point_[direction_sign[1]].y,
                                    box->point_[direction_sign[2]].z);
  const float3 max_point = (float3)(box->point_[1 - direction_sign[0]].x,
                                    box->point_[1 - direction_sign[1]].y,
                                    box->point_[1 - direction_sign[2]].z);
  const float3 t0 = fma(min_point, *inverse_ray_dir, *ood);
  const float3 t1 = fma(max_point, *inverse_ray_dir, *ood);
  const float tmin = max(max(t0.x, t0.y), t0.z);
  const float tmax = min(min(t1.x, t1.y), t1.z);
  return tmin <= tmax;

/*
  const float3 p0 = fma(box->point_[0], *inverse_ray_dir, *ood);
  const float3 p1 = fma(box->point_[1], *inverse_ray_dir, *ood);
  const float3 t0 = min(p0, p1);
  const float3 t1 = max(p0, p1);

  const float m0 = max(t0.x, t0.y);
  float m1 = min(t1.x, t1.y);
  const bool condition1 = t1.y < t0.x || t1.x < t0.y;
  const bool condition2 = t1.z < m0 || m1 < t0.z;
  m1 = min(m1, t1.z);

  return !condition1 && !condition2 && 0.0f <= m1;
  */
}
