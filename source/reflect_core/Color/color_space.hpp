/*!
  \file color_space.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_SPACE_HPP_
#define _REFLECT_COLOR_SPACE_HPP_

// Standard C++ library
#include <cstdint>
// Zisc
#include "zisc/matrix.hpp"
// Reflect
#include "reflect_config.hpp"

namespace reflect {

//! \addtogroup Color
//! \{

//! Get XYZ to RGB matrix.
Matrix3x3 getXyzToRgbMatrix(const std::uint32_t color_space);

//! Get RGB to XYZ matrix.
Matrix3x3 getRgbToXyzMatrix(const std::uint32_t color_space);

//! \} Color

} // namespace reflect

#endif // _REFLECT_COLOR_SPACE_HPP_
