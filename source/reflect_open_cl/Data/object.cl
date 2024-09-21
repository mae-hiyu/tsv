/*!
 \file object.cl
 \author takemura
 */

#include "object.h"

#include "intersection_point.h"
#include "ray.h"
#include "sampler.h"

const constant uchar kPlaneType = 0;

/*! \brief Test ray plane intersection */
bool isIntersectedPlane(const Object* object,
                        const Ray* ray,
                        IntersectionPoint* intersection);

/*! \brief sample a point on the plane */
float3 samplePlanePoint(const Object* object,
                        float* inverse_probability,
                        SamplerState* sampler);

/*! \brief sample a point on the plane */
float3 samplePlanePointImportance(const Object* object,
                                  const IntersectionPoint* intersection,
                                  float* inverse_probability,
                                  SamplerState* sampler);

/*!
 \details
 No detailed.
 */
bool isIntersectedObject(const Object* object,
                         const Ray* ray,
                         IntersectionPoint* intersection)
{
  bool is_intersected = false;
  switch(object->type_) {
   case kPlaneType:
    is_intersected = isIntersectedPlane(object, ray, intersection);
    break;
   default:
    break;
  }
  return is_intersected;
}

/*!
 \details
 No detailed.
 */
bool isIntersectedPlane(const Object* object,
                        const Ray* ray,
                        IntersectionPoint* intersection)
{
  // Calculate time t
  const float cos_theta = dot(object->axis_[2], ray->direction_);
  const float t = dot(object->point_ - ray->origin_, object->axis_[2]) / cos_theta;
  if (t < 0.0f)
    return false;

  const float3 point = fma(ray->direction_, t, ray->origin_);
  const float3 am = point - object->point_;
  const float dot_axis1_am = dot(am, object->axis_[0]);
  const float dot_axis2_am = dot(am, object->axis_[1]);
  const float square_width = dot(object->axis_[0], object->axis_[0]);
  const float square_height = dot(object->axis_[1], object->axis_[1]);
  if ((0.0f <= dot_axis1_am) && (dot_axis1_am <= square_width) &&
      (0.0f <= dot_axis2_am) && (dot_axis2_am <= square_height)) {
    const bool is_reverse_face = cos_theta > 0.0f;
    intersection->normal_ = (is_reverse_face) 
        ? -object->axis_[2]
        : object->axis_[2];
    intersection->point_ = point;
    const float u = dot_axis1_am / square_width;
    const float v = dot_axis2_am / square_height;
    intersection->texture_coordinate_ = (float2)(u, v);
    intersection->is_reverse_face_ = is_reverse_face;
    return true;
  }
  return false;
}

/*!
 \details
 No detailed.
 */
float3 sampleObjectPoint(const Object* object,
                         float* inverse_probability,
                         SamplerState* sampler)
{
  float3 point;
  switch (object->type_) {
   case kPlaneObject:
    point = samplePlanePoint(object, inverse_probability, sampler);
    break;
   default:
    break;
  }
  return point;
}

/*!
 \details
 No detailed.
 */
float3 sampleObjectPointImportance(const Object* object,
                                   const IntersectionPoint* intersection,
                                   float* inverse_probability,
                                   SamplerState* sampler)
{
  float3 point;
  switch (object->type_) {
   case kPlaneObject:
    point = samplePlanePointImportance(object, intersection, 
                                       inverse_probability, sampler);
    break;
   default:
    break;
  }
  return point;
}

/*! \brief sample a point on the plane */
float3 samplePlanePoint(const Object* object,
                        float* inverse_probability,
                        SamplerState* sampler)
{
  const float area = vload_half(0, &object->area_);
  *inverse_probability = 1.0f / area;

  const float3 tmp = fma(object->axis_[0], sample(sampler), object->point_);
  return fma(object->axis_[1], sample(sampler), tmp);
}

/*! \brief sample a point on the plane */
float3 samplePlanePointImportance(const Object* object,
                                  const IntersectionPoint* intersection,
                                  float* inverse_probability,
                                  SamplerState* sampler)
{
  return samplePlanePoint(object, inverse_probability, sampler);
}
