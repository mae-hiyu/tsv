/*!
  \file hdr_image-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_HDR_IMAGE_INL_HPP_
#define _REFLECT_HDR_IMAGE_INL_HPP_

#include "hdr_image.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "xyz_color.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
XyzColor& HdrImage::operator[](const std::size_t index)
{
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
const XyzColor& HdrImage::operator[](const std::size_t index) const
{
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
const XyzColor& HdrImage::get(const std::size_t x, const std::size_t y) const
{
  const std::size_t index = x + y * width_;
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
void HdrImage::set(const std::size_t x, const std::size_t y, const XyzColor& color)
{
  const std::size_t index = x + y * width_;
  buffer_[index] = color;
}

} // namespace reflect

#endif // _REFLECT_HDR_IMAGE_INL_HPP_
