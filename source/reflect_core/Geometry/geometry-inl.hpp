/*!
  \file geometry-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_GEOMETRY_INL_HPP_
#define _REFLECT_GEOMETRY_INL_HPP_

#include "geometry.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
double Geometry::surfaceArea() const
{
  return surface_area_;
}

} // namespace reflect

#endif // _REFLECT_GEOMETRY_INL_HPP_
