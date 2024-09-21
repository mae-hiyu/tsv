/*!
  \file cl_spectral_distribution.cpp
  \author takemura
  */

#include "cl_spectral_distribution.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "Color/spectral_distribution.hpp"
#include "OpenCL/Utility/cl_float.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ClSpectralDistribution toClDistribution(const SpectralDistribution& distribution)
{
  ClSpectralDistribution cl_distribution;
  for (std::size_t index = 0; index < distribution.size(); ++index)
    cl_distribution.distribution_[index] = toClHalf(distribution[index]);
  return cl_distribution;
}

/*!
  \details
  No detailed.
  */
template <>
std::size_t printMemberData<ClSpectralDistribution>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClSpectralDistribution::distribution_);
  return size;
}

} // namespace reflect
