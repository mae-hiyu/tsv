/*!
  \file    xyz_image-inl.hpp
  \author  takemura
*/

#pragma once

#include "spectra_image.hpp"
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "Sampling/sampled_spectra.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void XyzImage::addXyzContribution(
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  const std::size_t pixel_index = widthResolution() * y + x;
  auto& pixel = buffer_[pixel_index];
  for (std::size_t i = 0; i < kSampleSize; ++i) {
    // const std::size_t index = getIndex(contribution.wavelength(i));
    pixel[i] += contribution.intensity(i);
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void addXyzContribution(
    XyzImageInterface* image,
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  auto xyz_image = cast<XyzImage*>(image);
  xyz_image->addXyzContribution(x, y, contribution);
}

} // namespace reflect

