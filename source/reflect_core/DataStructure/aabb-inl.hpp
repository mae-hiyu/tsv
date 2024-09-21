/*!
 \file aabb-inl.hpp
 \author takemura
 */

#ifndef _REFLECT_AABB_INL_HPP_
#define _REFLECT_AABB_INL_HPP_

#include "aabb.hpp"
// Reflect
#include "LinearAlgebra/point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
Point3 Aabb::centroid() const
{
  return point_[0] + (point_[1] - point_[0]) * 0.5;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t Aabb::longestAxis() const
{
  constexpr std::size_t x = 0;
  constexpr std::size_t y = 1;
  constexpr std::size_t z = 2;
  const auto range = maxPoint() - minPoint();
  return (range[x] > range[y])
    ? (range[x] > range[z])
      ? x
      : z
    : (range[y] > range[z])
      ? y
      : z;
}
 
/*!
 \details
 No detailed.
 */
inline
const Point3& Aabb::maxPoint() const
{
  return point_[1];
} 

/*!
 \details
 No detailed.
 */
inline
const Point3& Aabb::minPoint() const
{
  return point_[0];
}

/*!
  \details
  No detailed.
  */
inline
double Aabb::surfaceArea() const
{
  const auto range = maxPoint() - minPoint();
  return 2.0 * (range[0] * range[1] + range[2] * range[1] + range[0] * range[2]);
}

/*!
  \details
  No detailed.
  */
inline
Aabb combine(const Aabb& a, const Aabb& b)
{
  const auto min_point = zisc::minElements(a.minPoint().data(),
                                           b.minPoint().data());
  const auto max_point = zisc::maxElements(a.maxPoint().data(),
                                           b.maxPoint().data());
  return Aabb{Point3{min_point}, Point3{max_point}};
}

} // namespace reflect

#endif // _REFLECT_AABB_INL_HPP_
