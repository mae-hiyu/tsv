/*!
  \file intersection_info-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_INTERSECTION_INFO_INL_HPP_
#define _REFLECT_INTERSECTION_INFO_INL_HPP_

#include "intersection_info.hpp"
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
IntersectionInfo::IntersectionInfo() :
    object_{nullptr},
    is_reverse_face_{false}
{
}

/*!
  \details
  No detailed.
  */
inline
IntersectionInfo::IntersectionInfo(const Point3& point,
                                   const Vector3& normal,
                                   const Object* object,
                                   const bool is_reverse_face) :
    point_{point},
    normal_{is_reverse_face ? -normal : normal},
    object_{object},
    is_reverse_face_{is_reverse_face}
{
}

/*!
  \details
  No detailed.
  */
inline
bool IntersectionInfo::isIntersected() const
{
  return object_ != nullptr;
}

/*!
  \details
  No detailed.
  */
inline
bool IntersectionInfo::isReverseFace() const
{
  return is_reverse_face_;
}

/*!
  \details
  No detailed.
  */
inline
const Vector3& IntersectionInfo::normal() const
{
  return normal_;
}

/*!
  \details
  No detailed.
  */
inline
const Object* IntersectionInfo::object() const
{
  return object_;
}

/*!
  \details
  No detailed.
  */
inline
const Point3& IntersectionInfo::point() const
{
  return point_;
}

/*!
  \details
  No detailed.
  */
inline
void IntersectionInfo::setReverseFace(const bool is_reverse_face)
{
  is_reverse_face_ = is_reverse_face;
}

/*!
  \details
  No detailed.
  */
inline
void IntersectionInfo::setNormal(const Vector3& normal)
{
  normal_ = is_reverse_face_ ? -normal : normal;
}

/*!
  \details
  No detailed.
  */
inline
void IntersectionInfo::setObject(const Object* object)
{
  object_ = object;
}

/*!
  \details
  No detailed.
  */
inline
void IntersectionInfo::setPoint(const Point3& point)
{
  point_ = point;
}

/*!
  \details
  No detailed.
  */
inline
void IntersectionInfo::setTextureCoordinate(const Point2& texture_coordinate)
{
  texture_coordinate_ = texture_coordinate;
}

/*!
  \details
  No detailed.
  */
inline
const Point2& IntersectionInfo::textureCoordinate() const
{
  return texture_coordinate_;
}

} // namespace reflect

#endif // _REFLECT_INTERSECTION_INFO_INL_HPP_
