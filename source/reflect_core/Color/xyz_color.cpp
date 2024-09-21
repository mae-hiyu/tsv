/*!
  \file xyz_color.cpp
  \author takemura
  */

#include "xyz_color.hpp"
// Zisc
#include "zisc/matrix.hpp"
// Reflect
#include "rgb_color.hpp"
#include "yxy_color.hpp"
#include "LinearAlgebra/transformation.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
RgbColor XyzColor::toRgb(const Matrix3x3& to_rgb_matrix) const
{
  return RgbColor{to_rgb_matrix * color_};
}

/*!
  \details
  No detailed.
  */
YxyColor XyzColor::toYxy() const
{
  const double normalization = 1.0 / color_.sum();
  return YxyColor{y(), x() * normalization, y() * normalization};
}

} // namespace reflect

