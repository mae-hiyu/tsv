/*!
  \file hdr_image.hpp
  \author takemura
  */

#ifndef _REFLECT_HDR_IMAGE_HPP_
#define _REFLECT_HDR_IMAGE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "xyz_color.hpp"

namespace reflect {

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
class HdrImage
{
 public:
  //! Create a hdr image
  HdrImage(const std::size_t width, const std::size_t height);

  //! Returh the pixel color by index
  XyzColor& operator[](const std::size_t index);

  //! Returh the pixel color by index
  const XyzColor& operator[](const std::size_t index) const;


  //! Return the pixel color
  const XyzColor& get(const std::size_t x, const std::size_t y) const;

  //! Set pixel color
  void set(const std::size_t x, const std::size_t y, const XyzColor& color);

 private:
  //! Initialize
  void initialize();


  std::vector<XyzColor> buffer_;
  std::size_t width_,
              height_;
};

//! \} Color

} // namespace reflect

#include "hdr_image-inl.hpp"

#endif // _REFLECT_HDR_IMAGE_HPP_
