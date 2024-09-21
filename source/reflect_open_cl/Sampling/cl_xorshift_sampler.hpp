/*!
  \file cl_xorshift_sampler.hpp
  \author takemura
  */

#ifndef _REFELCT_CL_XORSHIFT_SAMPLER_HPP_
#define _REFELCT_CL_XORSHIFT_SAMPLER_HPP_

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
struct ClXorshiftState
{
  //! Create a xorshift sampler
  ClXorshiftState(const cl_uint seed);


  //! Set seed
  void setSeed(const cl_uint seed);

  cl_uint state_[4];
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClXorshiftState>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClXorshiftState::state_);
  return size;
}

} // namespace reflect

#endif // _REFELCT_CL_XORSHIFT_SAMPLER_HPP_
