/*!
  \file rgb_color-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RGB_COLOR_INL_HPP_
#define _REFLECT_RGB_COLOR_INL_HPP_

#include "rgb_color.hpp"
// Standard C++ library
#include <cmath>
// Qt
#include <QColor>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "color.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
RgbColor::RgbColor()
{
}

/*!
  \details
  No detailed.
  */
inline
RgbColor::RgbColor(const double red, const double green, const double blue) :
    Color(red, green, blue)
{
}

/*!
  \details
  No detailed.
  */
inline
RgbColor::RgbColor(const QColor& color) :
    Color(cast<double>(color.red()) * (1.0 / 255.0),
          cast<double>(color.green()) * (1.0 / 255.0),
          cast<double>(color.blue()) * (1.0 / 255.0))
{
}

/*!
  \details
  No detailed.
  */
inline
RgbColor::RgbColor(const zisc::ArithmeticArray<double, 3>& color) :
    Color(color)
{
}

/*!
  \details
  No detailed.
  */
inline
void RgbColor::gammaCorrection(const double inverse_gamma)
{
  color_.setElements(std::pow(red(), inverse_gamma),
                     std::pow(green(), inverse_gamma),
                     std::pow(blue(), inverse_gamma));
}

/*!
  \details
  No detailed.
  */
inline
double& RgbColor::blue()
{
  return color_[2];
}

/*!
  \details
  No detailed.
  */
inline
const double& RgbColor::blue() const
{
  return color_[2];
}

/*!
  \details
  No detailed.
  */
inline
double& RgbColor::green()
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
const double& RgbColor::green() const
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
double& RgbColor::red()
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
const double& RgbColor::red() const
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
QRgb RgbColor::toQRgb() const
{
  constexpr double scale_factor = 255.0;
  const auto qt_color = color_ * scale_factor;
  return qRgb(cast<int>(qt_color[0]), cast<int>(qt_color[1]), cast<int>(qt_color[2]));
}

} // namespace reflect

#endif // _REFLECT_RGB_COLOR_INL_HPP_
