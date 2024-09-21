/*!
  \file cl_emitter_model.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_EMITTER_MODEL_HPP_
#define _REFLECT_CL_EMITTER_MODEL_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "OpenCL/cl.hpp"
#include "OpenCL/Color/cl_spectral_distribution.hpp"
#include "Utility/size.hpp"

namespace reflect {

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
struct ClEmitterModel
{
  ClSpectralDistribution distribution_;
  cl_half radiant_emittance_;
  cl_uchar type_;
};

//! Print member variable data
template <> inline
std::size_t printMemberData<ClEmitterModel>()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(ClEmitterModel::distribution_);
  size += PRINT_VARIABLE_DATA(ClEmitterModel::radiant_emittance_);
  size += PRINT_VARIABLE_DATA(ClEmitterModel::type_);
  return size;
}

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_EMITTER_MODEL_HPP_
