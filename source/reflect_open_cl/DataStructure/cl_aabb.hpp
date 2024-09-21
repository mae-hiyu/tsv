/*!
  \file cl_aabb.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_AABB_HPP_
#define _REFLECT_CL_AABB_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "OpenCL/cl.hpp"
#include "Utility/size.hpp"

namespace reflect {

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
struct ClAabb
{
  cl_float3 point_[2];
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClAabb>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClAabb::point_);
  return size;
}

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_AABB_HPP_
