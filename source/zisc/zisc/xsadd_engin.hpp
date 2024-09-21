/*!
  \file xsadd_engin.hpp
  \author takemura
  */

#ifndef _ZISC_XSADD_ENGIN_HPP_
#define _ZISC_XSADD_ENGIN_HPP_

// Standard C++ library
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>
// Zisc
#include "random_generator.hpp"

namespace zisc {

/*!
  \brief Xorshift-add random number generator
  \details
  No detailed.
  */
class XsaddEngin : public RandomGenerator<XsaddEngin>
{
 public:
  // For STL
  using result_type = std::uint32_t;


  //! Initialize generator using defualt random seed
  XsaddEngin();

  //! Initialize generator
  XsaddEngin(const std::uint32_t seed);


  //! Generate random number
  std::uint32_t operator()();


  //! Generate random number x satisfying a <= x < b
  template <typename Arithmetic>
  Arithmetic distribute(const Arithmetic a, const Arithmetic b);

  //! Generate random number
  std::uint32_t generate();

  //! Generate double precision floating point number x (0.0 <= x < 1.0)
  double generateDouble();

  //! Generate floating point number x (0.0 <= x < 1.0)
  float generateFloat();

  //! Return the largest possible value in the output range
  static constexpr std::uint32_t max()
  {
    return std::numeric_limits<std::uint32_t>::max();
  }

  //! Return the sammlest possible value in the output range
  static constexpr std::uint32_t min()
  {
    return std::numeric_limits<std::uint32_t>::min();
  }

  //! Set random seed
  void setSeed(const std::uint32_t seed);

  //! Set random seed
  void setSeed(const std::vector<std::uint32_t>& seed_array);

 private:
  //! Initialize
  std::uint32_t initializeValue1(const std::uint32_t x) const;

  //! Initialize
  std::uint32_t initializeValue2(const std::uint32_t x) const;

  //! Change internal state
  void nextState();

  //! Certificate period
  void periodCertification();


  static constexpr std::size_t loop_ = 8;


  std::uint32_t state_[4];
};

} // namespace zisc

#include "xsadd_engin-inl.hpp"

#endif // _ZISC_XSADD_ENGIN_HPP_
