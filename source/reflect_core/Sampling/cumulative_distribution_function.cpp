/*!
  \file cumulative_distribution_function.cpp
  \author takemura
  */

#include "cumulative_distribution_function.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
#include <utility>
// Reflect
#include "Color/spectral_distribution.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
CumulativeDistributionFunction::CumulativeDistributionFunction(
    const std::vector<double>& pdf)
{
  initialize(pdf);
}

/*!
  \details
  No detailed.
  */
CumulativeDistributionFunction::CumulativeDistributionFunction(
    const SpectralDistribution& pdf)
{
  initialize(pdf);
}

///*!
//  \details
//  No detailed.
//  */
//CumulativeDistributionFunction::CumulativeDistributionFunction(
//    CumulativeDistributionFunction&& other) :
//    distribution_{std::move(other.distribution_)}
//{
//}
//
///*!
//  \details
//  No detailed.
//  */
//CumulativeDistributionFunction& CumulativeDistributionFunction::operator=(
//    CumulativeDistributionFunction&& other)
//{
//  distribution_ = std::move(other.distribution_);
//  return *this;
//}

/*!
  \details
  No detailed.
  */
void CumulativeDistributionFunction::initialize(const std::vector<double>& pdf)
{
  distribution_.resize(pdf.size(), 0.0);
  double sum = 0.0;
  for (std::size_t index = 0; index < pdf.size(); ++index) {
    sum += pdf[index];
    distribution_[index] = sum;
  }
}

/*!
  \details
  No detailed.
  */
void CumulativeDistributionFunction::initialize(const SpectralDistribution& pdf)
{
  distribution_.resize(pdf.size(), 0.0);
  double sum = 0.0;
  for (std::size_t index = 0; index < pdf.size(); ++index) {
    sum += pdf[index];
    distribution_[index] = sum;
  }
}

} // namespace reflect
