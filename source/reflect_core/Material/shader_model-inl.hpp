/*!
  \file shader_model-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SHADER_MODEL_INL_HPP_
#define _REFLECT_SHADER_MODEL_INL_HPP_

#include "shader_model.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "Utility/size.hpp"

namespace reflect {

// Forward declaration
class IntersectionInfo;
class Sampler;
class SurfaceModel;

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
ShaderModel<kSampleSize>::ShaderModel()
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t ShaderModel<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  return size;
}

} // namespace reflect

#endif // _REFLECT_SHADER_MODEL_INL_HPP_
