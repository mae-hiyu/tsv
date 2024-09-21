/*!
  \file cl_xorshift_sampler.cpp
  \author takemura
  */

#include "cl_xorshift_sampler.hpp"
// Reflect
#include "OpenCL/cl.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ClXorshiftState::ClXorshiftState(const cl_uint seed)
{
  setSeed(seed);
}

/*!
  \details
  No detailed.
  */
void ClXorshiftState::setSeed(const cl_uint seed)
{
  state_[0] = seed;
  state_[1] = (seed >> 24) | (seed << 8);
  state_[2] = (seed >> 16) | (seed << 16);
  state_[3] = (seed >> 8) | (seed << 24);
}

} // namespace reflect
