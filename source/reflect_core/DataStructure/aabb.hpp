/*!
 \file aabb.hpp
 \author takemura
 */

#ifndef _REFLECT_AABB_HPP_
#define _REFLECT_AABB_HPP_

// Standard C++ library
#include <cstddef>
#include <utility>
// Reflect
#include "LinearAlgebra/point.hpp"

namespace reflect {

// Forward declaration
class Ray;

//! \addtogroup DataStructure
//! \{

/*!
 \brief AABB (Axis Aligned Bounding Box)
 \details
 No detailed.
 */
class Aabb
{
 public:
  //! Create AABB
  Aabb();

  //! Create AABB
  Aabb(const Point3& min, const Point3& max);


  //! Return the centroid point of AABB
  Point3 centroid() const;

  //! Check whether a ray intersects this AABB
  std::pair<bool, double> isIntersected(const Ray& ray) const;

  //! Return the longest axis number
  std::size_t longestAxis() const;

  //! Return the maximym point of AABB
  const Point3& maxPoint() const;

  //! Return the minimum point of AABB
  const Point3& minPoint() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Set the maximum point of AABB
  void setMaxPoint(const Point3& point);

  //! Set the minimum point of AABB
  void setMinPoint(const Point3& point);

  //! Return the surface area
  double surfaceArea() const;

 private:
  Point3 point_[2]; // Minimum and maximum point
};

//! Combine bounding boxs
Aabb combineBoundingBox(const Aabb& a, const Aabb& b);

//! \} DataStructure

} // namespace reflect

#include "aabb-inl.hpp"

#endif // _REFLECT_AABB_HPP_
