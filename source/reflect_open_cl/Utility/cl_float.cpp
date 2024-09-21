/*!
  \file cl_float.cpp
  \author takemura
  */

#include "cl_float.hpp"
// Standard C++ library
#include <cmath>
#include <cstdint>
#include <limits>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "OpenCL/cl.hpp"

namespace reflect {

using zisc::cast;

union FloatConversionUnion
{
  std::int32_t i_;
  float f_;
};

/*!
  \details
  reference: pocl cl_half.c
  */
cl_half toClHalf(const float value)
{
  FloatConversionUnion u;
  u.f_ = value;
  cl_half half = (u.i_ & 0x007FFFFF) >> 13;
  half |= (u.i_ & 0x07800000) >> 13;
  half |= (u.i_ & 0x40000000) >> 16;
  half |= (u.i_ & 0x80000000) >> 16;
  // TODO saturate overflows to inf
  return half;
}

/*!
  \details
  No detailed.
  */
cl_half toClHalf(const double value)
{
  return toClHalf(cast<float>(value));
}

/*!
  \details
  No detailed.
  */
float toFloat(cl_half value) 
{
  if (value == 0xFC00)
    return -std::numeric_limits<float>::infinity();
  if (value == 0x7C00)
    return std::numeric_limits<float>::infinity();

  const int sgn = ((value & 0x8000) >> 15);
  const int exp = (value & 0x7C00) >> 10;
  const int mant = value & 0x03FF;

  if (exp == 0x1F && mant != 0)
    return std::numeric_limits<float>::quiet_NaN();

  float v = (exp == 0) ? mant : mant | 0x0400; // 1.x if not denormal
  constexpr float t = 1.0f / cast<float>(0x400);
  v *= t;
  float mul = std::exp2(exp - 15);
  v *= mul;
  if (sgn)
    v *= -1;
  return v;
}

/*!
  \details
  No detailed.
  */
double toDouble(cl_half value)
{
  return cast<double>(toFloat(value));
}

} // namespace reflect
