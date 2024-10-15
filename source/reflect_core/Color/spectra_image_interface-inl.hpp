/*!
  \file spectra_image_interface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRA_IMAGE_INTERFACE_INL_HPP_
#define _REFLECT_SPECTRA_IMAGE_INTERFACE_INL_HPP_

#include "spectra_image_interface.hpp"
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
SpectraImageInterface::SpectraImageInterface(const std::size_t width,
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
void SpectraImageInterface::addContribution(
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  const auto image_type = type();
  switch (image_type) {
   case SpectraImageType::Spectra:
    addXYZSpectraContribution(this, x, y, contribution);
    break;
   case SpectraImageType::Rgb:
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
std::size_t SpectraImageInterface::printMemberData()
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
std::size_t SpectraImageInterface::heightResolution() const
{
  return height_;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t SpectraImageInterface::widthResolution() const
{
  return width_;
}

} // namespace reflect

#endif // _REFLECT_SPECTRA_IMAGE_INTERFACE_INL_HPP_
