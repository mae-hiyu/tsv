/*!
  \file cl_sampler.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SAMPLER_HPP_
#define _REFLECT_CL_SAMPLER_HPP_

// Standard C++ library
#include <string>
// Reflect
#include "OpenCL/cl.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class ClCore;

//! Make sampler buffer
template <typename SamplerType>
UniquePointer<cl::Buffer> makeSamplerBuffer(const QSettings& settings,
                                            const ClCore& core,
                                            const std::size_t size);

//! Get sampler build options
template <typename SamplerType>
std::string getSamplerOptions();

//! Get sampler source file name
template <typename SamplerType>
std::string getSamplerSource();

template <typename SamplerType>
struct ClSamplerType;

} // namespace reflect

#include "cl_sampler-inl.hpp"

#endif // _REFLECT_CL_SAMPLER_HPP_
