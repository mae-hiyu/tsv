/*!
  \file yxy_color.hpp
  \author takemura
  */

#ifndef _REFLECT_YXY_COLOR_HPP_
#define _REFLECT_YXY_COLOR_HPP_

// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "color.hpp"

namespace reflect {

// Forward decralation
class XyzColor;

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class YxyColor : public Color<3>
{
 public:
  //! Create Yxy
  YxyColor(const double Y, const double x, const double y);


  //! Return the x element reference
  double& x();

  //! Return the x element reference
  const double& x() const;

  //! Return the y element reference
  double& y();

  //! Return the y element reference
  const double& y() const;

  //! Return the Y element reference
  double& Y();

  //! Return the Y element reference
  const double& Y() const;

  //! Convert to XYZ
  XyzColor toXyz() const;
};

//! \} Color

} // namespace reflect

#include "yxy_color-inl.hpp"

#endif // _REFLECT_YXY_COLOR_HPP_
