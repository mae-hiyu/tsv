/*!
  \file cl_surface_scattering_model.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SURFACE_SCATTERING_MODEL_HPP_
#define _REFLECT_CL_SURFACE_SCATTERING_MODEL_HPP_

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
struct ClSurfaceScatteringModel
{
  cl_ushort parameter_[3];
  cl_uchar type_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClSurfaceScatteringModel>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClSurfaceScatteringModel::parameter_);
  size += PRINT_VARIABLE_DATA(ClSurfaceScatteringModel::type_);
  return size;
}

} // namespace reflect

#endif // _REFLECT_CL_SURFACE_SCATTERING_MODEL_HPP_
