/*!
 \file vector.cl
 \author takemura
 */

#include "vector.h"

const constant float threshold = 0.6f;

/*!
 \details
 No detailed.
 */
void changeBasisToNormal(const float3* normal, float3* v)
{
  float3 y_axis;
  const float3* z_axis = normal;
  if ((-threshold < z_axis->y) && (z_axis->y < threshold))
    y_axis.y = 1.0f;
  else if ((-threshold < z_axis->z) && (z_axis->z < threshold))
    y_axis.z = 1.0f;
  else
    y_axis.x = 1.0f;

  const float3 x_axis = normalize(cross(y_axis, *z_axis));
  y_axis = cross(*z_axis, x_axis);

  *v = v->x * x_axis + v->y * y_axis + v->z * *z_axis;
}
