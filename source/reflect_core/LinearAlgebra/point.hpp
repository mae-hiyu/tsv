/*!
  \file point.hpp
  \author takemura
  */

#ifndef _REFLECT_POINT_HPP_
#define _REFLECT_POINT_HPP_

// Zisc
#include "zisc/point.hpp"

namespace reflect {

//! \addtogroup LinearAlgebra
//! \{

using Point2 = zisc::Point<double, 2>;
using Point3 = zisc::Point<double, 3>;
using Point4 = zisc::Point<double, 4>;

//! Make 4d point from 3d point
Point4 makePoint4(const Point3& point, const double value);

//! Take 3d point from 4d point
Point3 takePoint3(const Point4& point);

//! \} LinearAlgebra

} // namespace reflect

#include "point-inl.hpp"

#endif // _REFLECT_POINT_HPP_
