/*!
  \file rgb_color.cpp
  \author takemura
  */

#include "rgb_color.hpp"
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/matrix.hpp"
// Reflect
#include "xyz_color.hpp"
#include "LinearAlgebra/transformation.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
XyzColor RgbColor::toXyz(const Matrix3x3& to_xyz_matrix) const
{
  return XyzColor{to_xyz_matrix * color_};
}

} // namespace reflect
