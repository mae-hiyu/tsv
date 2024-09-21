/*!
  \file xsadd_engin.cpp
  \author takemura
  */

#include "xsadd_engin.hpp"
// Standard C++ library
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>
// Zisc
#include "random_generator.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
void XsaddEngin::setSeed(const std::uint32_t seed)
{
  state_[0] = seed;
  state_[1] = 0;
  state_[2] = 0;
  state_[3] = 0;

  for (std::size_t i = 1; i < loop_; ++i) {
    constexpr std::uint32_t t = 1812433253u;
    state_[i & 3] ^= i + t * (state_[(i - 1) & 3] ^ (state_[(i - 1) & 3] >> 30));
  }
  periodCertification();
  for (std::size_t i = 0; i < loop_; ++i)
    nextState();
}

/*!
  \details
  No detailed.
  */
void XsaddEngin::setSeed(const std::vector<std::uint32_t>& seed_array)
{
  constexpr int lag = 1;
  constexpr int mid = 1;
  constexpr int size = 4;

  state_[0] = 0;
  state_[1] = 0;
  state_[2] = 0;
  state_[3] = 0;

  std::size_t count;
  if (seed_array.size() + 1 > loop_)
    count = seed_array.size() + 1;
  else
    count = loop_;
  std::uint32_t r = initializeValue1(state_[0] ^ 
                                     state_[mid % size] ^ 
                                     state_[(size - 1) % size]);
  state_[mid % size] += r;
  r += seed_array.size();
  state_[(mid + lag) % size] += r;
  state_[0] = r;
  --count;
  std::size_t i, j;
  for (i = 1, j = 0; (j < count) && (j < seed_array.size()); ++j) {
    r = initializeValue1(state_[i % size] ^ 
                         state_[(i + mid) % size] ^ 
                         state_[(i + size - 1) % size]);
    state_[(i + mid) % size] += r;
    r += seed_array[j] + i;
    state_[(i + mid + lag) % size] += r;
    state_[i % size] = r;
    i = (i + 1) % size;
  }
  for (; j < count; ++j) {
    r = initializeValue1(state_[i % size] ^
                         state_[(i + mid) % size] ^
                         state_[(i + size - 1) % size]);
    state_[(i + mid) % size] += r;
    r += i;
    state_[(i + mid + lag) % size] += r;
    state_[i % size] = r;
    i = (i + 1) % size;
  }
  for (j = 0; j < size; ++j) {
    r = initializeValue2(state_[i % size] +
                         state_[(i + mid) % size] +
                         state_[(i + size - 1) % size]);
    state_[(i + mid) % size] ^= r;
    r -= i;
    state_[(i + mid + lag) % size] ^= r;
    state_[i % size] = r;
    i = (i + 1) % size;
  }
  periodCertification();

  for (i = 0; i < loop_; ++i)
    nextState();
}

} // namespace zisc
