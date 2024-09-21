/*!
  \file xsadd_engin-inl.hpp
  \author takemura
  */

#ifndef _ZISC_XSADD_ENGIN_INL_HPP_
#define _ZISC_XSADD_ENGIN_INL_HPP_

#include "xsadd_engin.hpp"
// Standard C++ library
#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <vector>
// Zisc
#include "random_generator.hpp"
#include "utility.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
inline
XsaddEngin::XsaddEngin()
{
  setSeed(0);
}

/*!
  \details
  No detailed.
  */
inline
XsaddEngin::XsaddEngin(const std::uint32_t seed)
{
  setSeed(seed);
}

/*!
  \details
  No detailed.
  */
inline
std::uint32_t XsaddEngin::operator()()
{
  return generate();
}

/*!
  \details
  No detailed.
  */
inline
std::uint32_t XsaddEngin::generate()
{
  nextState();
  return state_[3] + state_[2];
}

/*!
  \details
  No detailed.
  */
inline
float XsaddEngin::generateFloat()
{
  constexpr float k = 1.0f / 4294967296.0f;
	return k * cast<float>(generate());
}

/*!
  \details
  No detailed.
  */
inline
double XsaddEngin::generateDouble()
{
  constexpr double k = 1.0 / 18446744073709551616.0;
  constexpr std::uint32_t t = 0xffffffe0u;

  std::uint64_t a = cast<std::uint64_t>(generate() & t);
  const std::uint64_t b = cast<std::uint64_t>(generate());
	a = (a << 32) | (b << 5);
	return k * cast<double>(a);
}

/*!
  \details
  No detailed.
  */
template <> inline
float XsaddEngin::distribute<float>(const float a, const float b)
{
  return a + generateFloat() * (b - a);
}

/*!
  \details
  No detailed.
  */
template <> inline
double XsaddEngin::distribute<double>(const double a,  const double b)
{
  return a + (1.0 - generateDouble()) * (b - a);
}

/*!
  \details
  No detailed.
  */
template <typename Integer> inline
Integer XsaddEngin::distribute(const Integer a, const Integer b)
{
  static_assert(std::is_integral<Integer>::value, 
                "## Integer must be integer type.");
  return a + cast<Integer>(generate()) % (b - a);
}

/*!
  \details
  No detailed.
  */
inline
std::uint32_t XsaddEngin::initializeValue1(const std::uint32_t x) const
{
  constexpr std::uint32_t t = 1664525u;
  return (x ^ (x >> 27)) * t;
}

/*!
  \details
  No detailed.
  */
inline
std::uint32_t XsaddEngin::initializeValue2(const std::uint32_t x) const
{
  constexpr std::uint32_t t = 1566083941u;
  return (x ^ (x >> 27)) * t;
}

/*!
  \details
  No detailed.
  */
inline
void XsaddEngin::nextState()
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
inline
void XsaddEngin::periodCertification()
{
  if (state_[0] == 0 && state_[1] == 0 && state_[2] == 0 && state_[3] == 0) {
    state_[0] = 'X';
    state_[1] = 'S';
    state_[2] = 'A';
    state_[3] = 'D';
  }
}

} // namespace zisc

#endif // _ZISC_XSADD_ENGIN_INL_HPP_
