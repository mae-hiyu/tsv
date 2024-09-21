/*!
  \file cl_point.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_POINT_HPP_
#define _REFLECT_CL_POINT_HPP_

// Reflect
#include "LinearAlgebra/point.hpp"
#include "OpenCL/cl.hpp"

namespace reflect {

//! Convert to OpenCL data type
cl_float3 toClPoint(const Point3& point);

} // namespace reflect

#endif // _REFLECT_CL_POINT_HPP_
