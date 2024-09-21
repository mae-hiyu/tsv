/*!
  \file cumulative_distribution_function-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_CUMULATIVE_DISTRIBUTION_FUNCTION_INL_HPP_
#define _REFLECT_CUMULATIVE_DISTRIBUTION_FUNCTION_INL_HPP_

#include "cumulative_distribution_function.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
std::size_t CumulativeDistributionFunction::inverseFunction(const double y) const
{
  auto position = std::lower_bound(distribution_.cbegin(), distribution_.cend(), y);
  return std::distance(distribution_.cbegin(), position);
}

} // namespace reflect

#endif // _REFLECT_CUMULATIVE_DISTRIBUTION_FUNCTION_INL_HPP_
