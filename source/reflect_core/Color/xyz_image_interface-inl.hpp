/*!
  \file    xyz_image_interface-inl.hpp
  \author takemura
*/

#pragma once

#include "xyz_image_interface.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "Utility/size.hpp"

namespace reflect {

// Forward declaration
template <std::size_t> class SampledSpectra;

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
XyzImageInterface::XyzImageInterface(const std::size_t width,
                                             const std::size_t height) :
    width_{width},
    height_{height}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void XyzImageInterface::addContribution(
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  const auto image_type = type();
  switch (image_type) {
   case XyzImageType::Spectra:
    addSpectraContribution(this, x, y, contribution);
    break;
   case XyzImageType::Rgb:
    addRgbContribution(this, x, y, contribution);
    break;
   default:
    zisc::raiseError("SpectraImageError: (type=", cast<int>(image_type),
                     " addContribution method is not implemented.");
    break;
  }
}

/*!
  \details
  No detailed.
  */
inline
std::size_t XyzImageInterface::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(width_);
  size += PRINT_VARIABLE_DATA(height_);
  return size;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t XyzImageInterface::heightResolution() const
{
  return height_;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t XyzImageInterface::widthResolution() const
{
  return width_;
}

} // namespace reflect

