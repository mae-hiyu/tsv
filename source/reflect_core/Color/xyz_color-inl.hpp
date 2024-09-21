/*!
  \file xyz_color-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_XYZ_COLOR_INL_HPP_
#define _REFLECT_XYZ_COLOR_INL_HPP_

#include "xyz_color.hpp"
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "rgb_color.hpp"
#include "yxy_color.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
XyzColor::XyzColor()
{
}

/*!
  \details
  No detailed.
  */
inline
XyzColor::XyzColor(const double x, const double y, const double z) :
    Color(x, y, z)
{
}

/*!
  \details
  No detailed.
  */
inline
XyzColor::XyzColor(const zisc::ArithmeticArray<double, 3>& color) :
    Color(color)
{
}

/*!
  \details
  No detailed.
  */
inline
double& XyzColor::x()
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
const double& XyzColor::x() const
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
double& XyzColor::y()
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
const double& XyzColor::y() const
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
double& XyzColor::z()
{
  return color_[2];
}

/*!
  \details
  No detailed.
  */
inline
const double& XyzColor::z() const
{
  return color_[2];
}

} // namespace reflect

#endif // _REFLECT_XYZ_COLOR_INL_HPP_
