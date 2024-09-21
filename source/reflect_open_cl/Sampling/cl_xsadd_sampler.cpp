/*!
  \file cl_sxadd_sampler.cpp
  \author takemura
  */

#include "cl_xsadd_sampler.hpp"
// Reflect
#include "OpenCL/cl.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ClXsaddState::ClXsaddState(const cl_uint seed)
{
  setSeed(seed);
}

/*!
  \details
  No detailed.
  */
void ClXsaddState::nextState()
{
  constexpr int sh1 = 15;
  constexpr int sh2 = 18;
  constexpr int sh3 = 11;

  std::uint32_t t = state_[0];
  t ^= t << sh1;
  t ^= t >> sh2;
  t ^= state_[3] << sh3;
  state_[0] = state_[1];
  state_[1] = state_[2];
  state_[2] = state_[3];
  state_[3] = t;
}

/*!
  \details
  No detailed.
  */
void ClXsaddState::periodCertification()
{
  if (state_[0] == 0 && state_[1] == 0 && state_[2] == 0 && state_[3] == 0) {
    state_[0] = 'X';
    state_[1] = 'S';
    state_[2] = 'A';
    state_[3] = 'D';
  }
}

/*!
  \details
  No detailed.
  */
void ClXsaddState::setSeed(const cl_uint seed)
{
  state_[0] = seed;
  state_[1] = 0;
  state_[2] = 0;
  state_[3] = 0;

  for (std::size_t i = 0; i < loop_; ++i) {
    constexpr std::uint32_t t = 1812433253u;
    state_[i & 3] ^= i + t * (state_[(i - 1) & 3] ^ (state_[(i - 1) & 3] >> 30));
  }
  periodCertification();
  for (std::size_t i = 0; i < loop_; ++i)
    nextState();
}

} // namespace reflect
