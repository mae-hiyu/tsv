/*!
  \file cl_light_source_reference.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_LIGHT_SOURCE_REFERENCE_HPP_
#define _REFLECT_CL_LIGHT_SOURCE_REFERENCE_HPP_

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
struct ClLightSourceReference
{
  cl_uint object_index_;
  cl_half weight_,
          inverse_weight_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClLightSourceReference>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClLightSourceReference::object_index_);
  size += PRINT_VARIABLE_DATA(ClLightSourceReference::weight_);
  size += PRINT_VARIABLE_DATA(ClLightSourceReference::inverse_weight_);
  return size;
}

} // namespace reflect

#endif // _REFLECT_CL_LIGHT_SOURCE_REFERENCE_HPP_
