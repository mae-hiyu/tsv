/*!
  \file rgb_color.hpp
  \author takemura
  */

#ifndef _REFLECT_RGB_COLOR_HPP_
#define _REFLECT_RGB_COLOR_HPP_

// Qt
#include <QColor>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "color.hpp"
#include "reflect_config.hpp"

// Forward declaration
class QColor;

namespace reflect {

//! Forward decralation
class XyzColor;

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class RgbColor : public Color<3>
{
 public:
  //! Create RGB
  RgbColor();

  //! Create RGB
  RgbColor(const double red, const double green, const double blur);

  //! Create RGB
  RgbColor(const QColor& color);

  //! Create RGB
  RgbColor(const zisc::ArithmeticArray<double, 3>& color);


  //! Apply gamma correction
  void gammaCorrection(const double inverse_gamma);

  //! Return the blue element reference.
  double& blue();

  //! Return the blue element reference.
  const double& blue() const;

  //! Return the green element reference.
  double& green();

  //! Return the green element reference.
  const double& green() const;

  //! Return the red element reference.
  double& red();

  //! Return the red element reference.
  const double& red() const;

  //! Convert RGB to Qt RGB format
  QRgb toQRgb() const;

  //! Convert RGB to XYZ.
  XyzColor toXyz(const Matrix3x3& to_xyz_matrix) const;
};

//! \} Color

} // namespace reflect

#include "rgb_color-inl.hpp"

#endif // _REFLECT_RGB_COLOR_HPP_
