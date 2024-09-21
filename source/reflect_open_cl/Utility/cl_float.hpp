/*!
  \file cl_float.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_FLOAT_HPP_
#define _REFLECT_CL_FLOAT_HPP_

// Reflect
#include "OpenCL/cl.hpp"

namespace reflect {

//! Convert float to OpenCL half type
cl_half toClHalf(const float value);

//! Convert double to OpenCL half type
cl_half toClHalf(const double value);

//! Convert cl_half to float
float toFloat(const cl_half value);

//! Convert cl_half to double 
double toDouble(const cl_half value);

} // namespace reflect

#endif // _REFLECT_CL_FLOAT_HPP_
