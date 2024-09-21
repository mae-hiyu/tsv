/*!
  \file random_generator-inl.hpp
  \author takemura
  */

#ifndef _ZISC_RANDOM_GENERATOR_INL_HPP_
#define _ZISC_RANDOM_GENERATOR_INL_HPP_

#include "random_generator.hpp"
// Standard C++ library
#include <cstdint>
#include <type_traits>
// Zisc
#include "utility.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename DerivedClass> template <typename Arithmetic> inline
Arithmetic RandomGenerator<DerivedClass>::distribute(const Arithmetic a,
                                                     const Arithmetic b)
{
  static_assert(std::is_arithmetic<Arithmetic>::value,
                "## Arguments must be arithmetic type.");
  return cast<DerivedClass*>(this)->distribute(a, b);
}

/*!
  \details
  No detailed.
  */
template <typename DerivedClass> inline
void RandomGenerator<DerivedClass>::setSeed(const std::uint32_t seed)
{
  cast<DerivedClass*>(this)->setSeed(seed);
}

/*!
  \details
  No detailed.
  */
template <typename DerivedClass> inline
RandomGenerator<DerivedClass>::RandomGenerator()
{
}

} // namespace zisc

#endif // _ZISC_RANDOM_GENERATOR_INL_HPP_
