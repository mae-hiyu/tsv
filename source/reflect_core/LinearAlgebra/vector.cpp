/*!
  \file vector.cpp
  \author takemura
  */

#include "vector.hpp"
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/utility.hpp"
#include "zisc/vector.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
void changeBasis(const Vector3& z_dir, Vector3* vector)
{
  using zisc::dot;

  Vector3 y_dir;
  constexpr double kThreshold = 0.6;
  if ((-kThreshold < z_dir[1]) && (z_dir[1] < kThreshold))
    y_dir.set(1, 1.0);
  else if ((-kThreshold < z_dir[2]) && (z_dir[2] < kThreshold))
    y_dir.set(2, 1.0);
  else
    y_dir.set(0, 1.0);

  const auto x_dir = zisc::cross(y_dir, z_dir).normalized();
  y_dir = zisc::cross(z_dir, x_dir);

  const auto& vec = *vector;
  *vector = vec[0] * x_dir + vec[1] * y_dir + vec[2] * z_dir;
}

} // namespace reflect
