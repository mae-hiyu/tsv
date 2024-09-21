/*!
  \file color_system.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_SYSTEM_HPP_
#define _REFLECT_COLOR_SYSTEM_HPP_

// Standard C++ library
#include <cstddef>
#include <cstdint>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "Color/rgb_color_matching_function.hpp"
#include "Color/xyz_color_matching_function.hpp"
#include "Tonemapping/tonemapping_method.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

//! \addtogroup RendererBase
//! \{

/*!
  \details
  No detailed.
  */
class ColorSystem
{
 public:
  //! Create system
  ColorSystem(const QSettings& settings);


  //! Return the color space
  std::uint32_t colorSpace() const;

  //! Initialize
  void initialize(const QSettings& settings);

  //! Check if RGB rendering mode is on
  bool isRgbRenderingMode() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the rgb color matching function
  const RgbColorMatchingFunction& rgbColorMatchingFunction() const;

  //! Return the tonemapping method
  const TonemappingMethod& tonemappingMethod() const;

  //! Return the color matching function
  const XyzColorMatchingFunction& xyzColorMatchingFunction() const;

 private:
  bool is_rgb_rendering_mode_;
  std::uint32_t color_space_;
  UniquePointer<RgbColorMatchingFunction> rgb_color_matching_function_;
  UniquePointer<XyzColorMatchingFunction> xyz_color_matching_function_;
  UniquePointer<TonemappingMethod> tonemapping_method_;
};

//! \} RendererBase

} // namespace reflect

#include "color_system-inl.hpp"

#endif // _REFLECT_COLOR_SYSTEM_HPP_
