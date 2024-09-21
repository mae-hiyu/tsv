/*!
  \file cl_vector.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_VECTOR_HPP_
#define _REFLECT_CL_VECTOR_HPP_

// Reflect
#include "LinearAlgebra/vector.hpp"
#include "OpenCL/cl.hpp"

namespace reflect {

//! Convert to OpenCL data type
cl_float3 toClVector(const Vector3& vector);

} // namespace reflect

#endif // _REFLECT_CL_VECTOR_HPP_
