/*!
  \file cl_point.cpp
  \author takemura
  */

#include "cl_point.hpp"
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "LinearAlgebra/point.hpp"
#include "OpenCL/cl.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
cl_float3 toClPoint(const Point3& point)
{
  return cl_float3{{cast<cl_float>(point[0]), 
                    cast<cl_float>(point[1]), 
                    cast<cl_float>(point[2])}};
}

} // namespace reflect
