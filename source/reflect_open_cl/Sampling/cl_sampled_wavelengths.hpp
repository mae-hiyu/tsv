/*!
  \file cl_sampled_wavelengths.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SAMPLED_WAVELENGTHS_HPP_
#define _REFLECT_CL_SAMPLED_WAVELENGTHS_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "cl_reflect_config.hpp"
#include "reflect_config.hpp"
#include "OpenCL/cl.hpp"
#include "Utility/size.hpp"

namespace reflect {

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
struct ClSampledWavelengths
{
  ClIntensitySamples inverse_probabilities_;
  cl_ushort wavelengths_[kSpectraSampleSize];
  cl_ushort primary_wavelength_index_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClSampledWavelengths>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClSampledWavelengths::inverse_probabilities_);
  size += PRINT_VARIABLE_DATA(ClSampledWavelengths::wavelengths_);
  size += PRINT_VARIABLE_DATA(ClSampledWavelengths::primary_wavelength_index_);
  return size;
}

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_SAMPLED_WAVELENGTHS_HPP_
