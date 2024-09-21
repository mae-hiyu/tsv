/*!
  \file random_generator.hpp
  \author takemura
  */

#ifndef _ZISC_RANDOM_GENERATOR_HPP_
#define _ZISC_RANDOM_GENERATOR_HPP_

// Standard C++ library
#include <cstdint>

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename DerivedClass>
class RandomGenerator
{
 public:
  using GeneratorType = DerivedClass;


  //! Generator random number x satisfying a <= x < b
  template <typename Arithmetic>
  Arithmetic distribute(const Arithmetic a, const Arithmetic b);

  //! Set random seed
  void setSeed(const std::uint32_t seed);

 protected:
  RandomGenerator();
};

} // namespace zisc

#include "random_generator-inl.hpp"

#endif // _ZISC_RANDOM_GENERATOR_HPP_
