/*!
  \file cl_object.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_OBJECT_HPP_
#define _REFLECT_CL_OBJECT_HPP_

// Standard C++ library
#include <cstddef>
// OpenCL
#include "OpenCL/cl.hpp"
#include "Utility/size.hpp"

namespace reflect {

//! \addtogroup OpenCL
//! \{

/*!
  \details
  Object data structure for OpenCL
  */
struct ClObject
{
  cl_float3 axis_[3];
  cl_float3 point_;
  cl_ushort surface_scattering_index_;
  cl_ushort emitter_index_;
  cl_half area_;
  cl_uchar type_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClObject>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClObject::axis_);
  size += PRINT_VARIABLE_DATA(ClObject::point_);
  size += PRINT_VARIABLE_DATA(ClObject::surface_scattering_index_);
  size += PRINT_VARIABLE_DATA(ClObject::emitter_index_);
  size += PRINT_VARIABLE_DATA(ClObject::area_);
  size += PRINT_VARIABLE_DATA(ClObject::type_);
  return size;
}

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_OBJECT_HPP_
