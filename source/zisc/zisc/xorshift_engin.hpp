/*!
 \file xorshift_engin.hpp
 \author takemura
 */

#ifndef _ZISC_XORSHFIT_ENGIN_HPP_
#define _ZISC_XORSHFIT_ENGIN_HPP_

// Standard C++ library
#include <cstdint>
#include <limits>
// Zisc
#include "random_generator.hpp"

namespace zisc {

/*!
 \brief Xorshift random number generator
 \details
 No detailed.
 */
class XorshiftEngin : public RandomGenerator<XorshiftEngin>
{
 public:
  // For STL
  using result_type = std::uint32_t; 


  //! Initialize generator using default random seed
  XorshiftEngin();

  //! Initialize generator
  XorshiftEngin(const std::uint32_t seed);


  //! Generate random number
  std::uint32_t operator()();


  //! Generate random number x satisfying a <= x < b
  template <typename Arithmetic>
  Arithmetic distribute(const Arithmetic a, const Arithmetic b);

  //! Generate random number
  std::uint32_t generate();

  //! Get the largest possible value in the output range
  static constexpr std::uint32_t max()
  {
    return std::numeric_limits<std::uint32_t>::max();
  }

  //! Get the smallest possible value in the output range
  static constexpr std::uint32_t min()
  {
    return std::numeric_limits<std::uint32_t>::min();
  }

  //! Set random seed
  void setSeed(const std::uint32_t seed);

  //! Set random seed
  void setSeed(const std::uint32_t seed1, const std::uint32_t seed2,
               const std::uint32_t seed3, const std::uint32_t seed4);

 private:
  std::uint32_t seed_[4];
};

} // namespace zisc

#include "xorshift_engin-inl.hpp"

#endif // _ZISC_XORSHFIT_ENGIN_HPP_
