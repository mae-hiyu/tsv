/*!
  \file ray.cpp
  \author takemura
  */

#include "ray.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
std::size_t Ray::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(origin_);
  size += PRINT_VARIABLE_DATA(direction_);
  size += PRINT_VARIABLE_DATA(inverse_direction_);
  size += PRINT_VARIABLE_DATA(sign_);
  size += PRINT_VARIABLE_DATA(is_alive_);
  return size;
}

} // namespace reflect
