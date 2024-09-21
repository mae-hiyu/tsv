/*!
  \file cl_spectral_distribution.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SPECTRAL_DISTRIBUTION_HPP_
#define _REFLECT_CL_SPECTRAL_DISTRIBUTION_HPP_

// Reflect
#include "reflect_config.hpp"
#include "OpenCL/cl.hpp"

namespace reflect {

// Forward declaration
class SpectralDistribution;

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
struct ClSpectralDistribution
{
  cl_half distribution_[kSpectraSize];
};

//! Convert to OpenCL data type
ClSpectralDistribution toClDistribution(const SpectralDistribution& distribution);

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_SPECTRAL_DISTRIBUTION_HPP_
