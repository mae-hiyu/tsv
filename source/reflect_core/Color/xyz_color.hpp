/*!
  \file xyz_color.hpp
  \author takemura
  */

#ifndef _REFLECT_XYZ_COLOR_HPP_
#define _REFLECT_XYZ_COLOR_HPP_

// Zisc
#include "zisc/arithmetic_array.hpp"
// Qt
#include <QColor>
// Reflect
#include "reflect_config.hpp"
#include "color.hpp"

namespace reflect {

// Forward decralation
class RgbColor;
class YxyColor;

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class XyzColor : public Color<3>
{
 public:
  //! Initialize XYZ color with 0
  XyzColor();

  //! Create XYZ color
  XyzColor(const double x, const double y, const double z);

  //! Create XYZ color
  XyzColor(const zisc::ArithmeticArray<double, 3>& color);


  //! Convert XYZ to RGB.
  RgbColor toRgb(const Matrix3x3& to_rgb_matrix) const;

  //! Convert XYZ to Yxy.
  YxyColor toYxy() const;

  //! Return the x element reference
  double& x();

  //! Return the x element reference
  const double& x() const;

  //! Return the y element reference
  double& y();

  //! Return the y element reference
  const double& y() const;

  //! Return the z element reference
  double& z();

  //! Return the z element reference
  const double& z() const;
};

//! \} Color

} // namespace reflect

#include "xyz_color-inl.hpp"

#endif // _REFLECT_XYZ_COLOR_HPP_
