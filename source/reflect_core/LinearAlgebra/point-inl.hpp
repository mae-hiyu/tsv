/*!
  \file point-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_POINT_INL_HPP_
#define _REFLECT_POINT_INL_HPP_

#include "point.hpp"
// Zisc
#include "zisc/point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
Point4 makePoint4(const Point3& point, const double value)
{
  return Point4{point[0], point[1], point[2], value};
}

/*!
  \details
  No detailed.
  */
inline
Point3 takePoint3(const Point4& point)
{
  return Point3{point[0], point[1], point[2]};
}

} // namespace reflect

#endif // _REFLECT_POINT_INL_HPP_
