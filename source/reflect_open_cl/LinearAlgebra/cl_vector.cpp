/*!
  \file cl_vector.cpp
  \author takemura
  */

#include "cl_vector.hpp"
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "LinearAlgebra/vector.hpp"
#include "OpenCL/cl.hpp"

namespace reflect {

using zisc::cast;
  
/*!
  \details
  No detailed.
  */
cl_float3 toClVector(const Vector3& vector)
{
  return cl_float3{{cast<cl_float>(vector[0]),
                    cast<cl_float>(vector[1]),
                    cast<cl_float>(vector[2])}};
}

} // namespace reflect
