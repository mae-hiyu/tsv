/*!
  \file cl_weight.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_WEIGHT_HPP_
#define _REFLECT_CL_WEIGHT_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "OpenCL/cl.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
struct ClWeight
{
  cl_uint index_;
  cl_ushort parameter_[2];
  cl_uchar type_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClWeight>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClWeight::index_);
  size += PRINT_VARIABLE_DATA(ClWeight::parameter_);
  size += PRINT_VARIABLE_DATA(ClWeight::type_);
  return size;
}

} // namespace reflect

#endif // _REFLECT_CL_WEIGHT_HPP_
