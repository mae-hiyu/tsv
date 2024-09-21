/*!
  \file yxy_color-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_YXY_COLOR_INL_HPP_
#define _REFLECT_YXY_COLOR_INL_HPP_

// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "color.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
YxyColor::YxyColor(const double Y, const double x, const double y) :
    Color(Y, x, y)
{
}

/*!
  \details
  No detailed.
  */
inline
double& YxyColor::x()
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
const double& YxyColor::x() const
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
double& YxyColor::y()
{
  return color_[2];
}

/*!
  \details
  No detailed.
  */
inline
const double& YxyColor::y() const
{
  return color_[2];
}

/*!
  \details
  No detailed.
  */
inline
double& YxyColor::Y()
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
const double& YxyColor::Y() const
{
  return color_[0];
}

} // namespace reflect

#endif // _REFLECT_YXY_COLOR_INL_HPP_
