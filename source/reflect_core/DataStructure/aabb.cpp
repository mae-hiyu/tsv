/*!
 \file aabb.cpp
 \author takemura
 */

#include "aabb.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "Data/ray.hpp"
#include "Utility/size.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
Aabb::Aabb()
{
}

/*!
  \details
  No detailed.
  */
Aabb::Aabb(const Point3& min, const Point3& max) :
    point_{min, max}
{
}

/*!
  \details
  Please see the details of this algorithm below URL.
  http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-box-intersection/
  */
std::pair<bool, double> Aabb::isIntersected(const Ray& ray) const
{
  const auto sign = ray.sign();
  const Point3 min_point{point_[sign[0]][0], 
                         point_[sign[1]][1], 
                         point_[sign[2]][2]};
  const Point3 max_point{point_[1 - sign[0]][0], 
                         point_[1 - sign[1]][1], 
                         point_[1 - sign[2]][2]};
  auto t0 = (min_point - ray.origin()).data() * ray.inverseDirection().data();
  auto t1 = (max_point - ray.origin()).data() * ray.inverseDirection().data();
  const auto tmin = std::max(std::max(t0[0], t0[1]), t0[2]);
  const auto tmax = std::min(std::min(t1[0], t1[1]), t1[2]);
  return std::make_pair(tmin <= tmax, tmin);
}

/*!
  \details
  No detailed.
  */
std::size_t Aabb::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(point_);
  return size;
}

/*!
  \details
  No detailed.
  */
void Aabb::setMaxPoint(const Point3& point)
{
  point_[1] = point;
}

/*!
 \details
 No detailed.
 */
void Aabb::setMinPoint(const Point3& point)
{
  point_[0] = point;
}

} // namespace reflect
