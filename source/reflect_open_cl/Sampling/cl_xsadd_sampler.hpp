/*!
  \file cl_xsadd_sampler.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_XSADD_SAMPLER_HPP_
#define _REFLECT_CL_XSADD_SAMPLER_HPP_

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
struct ClXsaddState
{
  //! Create a XS-add sampler
  ClXsaddState(const cl_uint seed);


  //! Next state
  void nextState();

  //! Certificate period
  void periodCertification();

  //! Set seed
  void setSeed(const cl_uint seed);


  static constexpr std::size_t loop_ = 8;
  cl_uint state_[4];
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClXsaddState>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClXsaddState::state_);
  return size;
}

} // namespace reflect

#endif // _REFLECT_CL_XSADD_SAMPLER_HPP_
