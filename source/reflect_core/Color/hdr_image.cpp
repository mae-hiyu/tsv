/*!
  \file hdr_image.cpp
  \author takemura
  */

#include "hdr_image.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "xyz_color.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
HdrImage::HdrImage(const std::size_t width, const std::size_t height) :
    width_{width},
    height_{height}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void HdrImage::initialize()
{
  const std::size_t buffer_size = width_ * height_;
  buffer_.resize(buffer_size);
}

} // namespace reflect
