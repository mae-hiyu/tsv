/*!
  \file intersectionpoint_point.cpp
  \author takemura
  */

#include "intersection_info.hpp"
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
std::size_t IntersectionInfo::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(point_);
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(texture_coordinate_);
  size += PRINT_VARIABLE_DATA(object_);
  size += PRINT_VARIABLE_DATA(is_reverse_face_);
  return size;
}

} // namespace reflect
