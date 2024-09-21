/*!
  \file intersection_info.hpp
  \author takemura
  */

#ifndef _REFLECT_INTERSECTION_INFO_HPP_
#define _REFLECT_INTERSECTION_INFO_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

// Forward declaration
class Object;

//! \addtogroup Data
//! \{

/*!
  \brief The information of ray-geometry intersection point
  \details
  No detailed.
  */
class IntersectionInfo
{
 public:
  //! Create a empty data
  IntersectionInfo();

  //! Create a intersection data
  IntersectionInfo(const Point3& point,
                   const Vector3& normal,
                   const Object* object, 
                   const bool is_reverse_face);


  //! Check if there is a intersected object
  bool isIntersected() const;

  //! Check if the intersection point is reverse face
  bool isReverseFace() const;

  //! Return the oriented normal direction
  const Vector3& normal() const;

  //! Return the intersected object
  const Object* object() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the intersection point
  const Point3& point() const;

  //! Set reverse face
  void setReverseFace(const bool is_reverse_face);
  
  //! Set normal direction
  void setNormal(const Vector3& normal);

  //! Set intersected object
  void setObject(const Object* object);

  //! Set intersection point
  void setPoint(const Point3& point);

  //! Set texture coordinate
  void setTextureCoordinate(const Point2& texture_coordinate);

  //! Return the texture coordinate
  const Point2& textureCoordinate() const;

 private:
  Point3 point_;
  Vector3 normal_;
  Point2 texture_coordinate_;
  const Object* object_;
  bool is_reverse_face_;
};

//! \} Data

} // namespace reflect

#include "intersection_info-inl.hpp"

#endif // _REFLECT_INTERSECTION_INFO_HPP_
