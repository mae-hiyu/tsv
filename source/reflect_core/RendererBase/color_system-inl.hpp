/*!
  \file color_system-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_SYSTEM_INL_HPP_
#define _REFLECT_COLOR_SYSTEM_INL_HPP_

#include "color_system.hpp"
// Standard C++ library
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "Color/xyz_color_matching_function.hpp"
#include "Tonemapping/tonemapping_method.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
const XyzColorMatchingFunction& ColorSystem::xyzColorMatchingFunction() const
{
  return *xyz_color_matching_function_;
}

/*!
  \details
  No detailed.
  */
inline
std::uint32_t ColorSystem::colorSpace() const
{
  return color_space_;
}

/*!
  \details
  No detailed.
  */
inline
bool ColorSystem::isRgbRenderingMode() const
{
  return is_rgb_rendering_mode_;
}

/*!
  \details
  No detailed.
  */
inline
const RgbColorMatchingFunction& ColorSystem::rgbColorMatchingFunction() const
{
  return *rgb_color_matching_function_;
}

/*!
  \details
  No detailed.
  */
inline
const TonemappingMethod& ColorSystem::tonemappingMethod() const
{
  return *tonemapping_method_;
}

} // namespace reflect

#endif // _REFLECT_COLOR_SYSTEM_INL_HPP_
