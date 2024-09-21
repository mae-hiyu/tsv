/*!
  \file cumulative_distribution_function.hpp
  \author takemura
  */

#ifndef _REFLECT_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP_
#define _REFLECT_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>

namespace reflect {

// Forward declaration
class SpectralDistribution;

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
class CumulativeDistributionFunction
{
 public:
  //! Create a cumulative distribution function from pdf
  CumulativeDistributionFunction(const std::vector<double>& pdf);

  //! Create a cumulative distribution function from pdf
  CumulativeDistributionFunction(const SpectralDistribution& pdf);

  //! Move data
//  CumulativeDistributionFunction(CumulativeDistributionFunction&& other);


  //! Move data
//  CumulativeDistributionFunction& operator=(CumulativeDistributionFunction&& other);


  //! Return the x value associated with the y value
  std::size_t inverseFunction(const double y) const;

 private:
  //! Initialize
  void initialize(const std::vector<double>& pdf);

  //! Initialize
  void initialize(const SpectralDistribution& pdf);


  std::vector<double> distribution_;
};

//! \} Sampling

} // namespace reflect

#include "cumulative_distribution_function-inl.hpp"

#endif // _REFLECT_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP_
