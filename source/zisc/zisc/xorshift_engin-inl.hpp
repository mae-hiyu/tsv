/*!
 \file xorshift_engin-inl.hpp
 \author takemura
 */

#ifndef _ZISC_XORSHIFT_ENGIN_INL_HPP_
#define _ZISC_XORSHIFT_ENGIN_INL_HPP_

#include "xorshift_engin.hpp"
// Standard C++ library
#include <cstdint>
#include <limits>
#include <type_traits>
// Zisc
#include "random_generator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace zisc {

/*!
 \details
 No detailed.
 */
inline
XorshiftEngin::XorshiftEngin()
{
  setSeed(123456789, 362436069, 521288629, 88675123);
}

/*!
 \details
 No detailed.
 */
inline
XorshiftEngin::XorshiftEngin(const std::uint32_t seed)
{
  setSeed(seed);
}

/*!
 \details
 No detailed.
 */
inline
std::uint32_t XorshiftEngin::operator()()
{
  return generate();
}

namespace inner {

/*!
  \details
  No detailed.
  */
template <typename Float, EnableIfFloat<Float> = kEnabler> inline
Float xorshiftDistribute(const Float a, const Float b, XorshiftEngin& xorshift)
{
  constexpr Float normalizer = cast<Float>(1.0) / cast<Float>(XorshiftEngin::max());
  constexpr Float epsilon = std::numeric_limits<Float>::epsilon();
  const Float random = cast<Float>(xorshift.generate()) * normalizer;
  return a + random * ((b - epsilon) - a);
}

/*!
  \details
  No detailed.
  */
template <typename Integer, EnableIfInteger<Integer> = kEnabler> inline
Integer xorshiftDistribute(const Integer a, const Integer b, XorshiftEngin& xorshift)
{
  return a + cast<Integer>(xorshift.generate()) % (b - a);
}

} // namespace inner

/*!
  \details
  No detailed.
  */
template <typename Arithmetic> inline
Arithmetic XorshiftEngin::distribute(const Arithmetic a, const Arithmetic b)
{
  static_assert(std::is_arithmetic<Arithmetic>::value,
                "## Arguments must be arithmetic type.");
  return inner::xorshiftDistribute(a, b, *this);
}

/*!
 \details
 No detailed.
 */
inline
std::uint32_t XorshiftEngin::generate()
{
  const std::uint32_t temp = seed_[0] ^ (seed_[0] << 11);
  seed_[0] = seed_[1];
  seed_[1] = seed_[2];
  seed_[2] = seed_[3];
  seed_[3] = (seed_[3] ^ (seed_[3] >> 19)) ^ (temp ^ (temp >> 8));
  return seed_[3];
}

/*!
 \details
 No detailed.
 */
inline
void XorshiftEngin::setSeed(const std::uint32_t seed)
{
  setSeed(seed,
          (seed >> 24) | (seed << 8),
          (seed >> 16) | (seed << 16),
          (seed >> 8) | (seed << 24));
}

/*!
 \details
 No detailed.
 */
inline
void XorshiftEngin::setSeed(const std::uint32_t seed1, 
                            const std::uint32_t seed2,
                            const std::uint32_t seed3,
                            const std::uint32_t seed4)
{
  seed_[0] = seed1;
  seed_[1] = seed2;
  seed_[2] = seed3;
  seed_[3] = seed4;
}

} // namespace zisc

#endif // _ZISC_XORSHIFT_ENGIN_INL_HPP_
