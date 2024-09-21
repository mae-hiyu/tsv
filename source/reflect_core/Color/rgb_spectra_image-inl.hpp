/*!
  \file rgb_spectra_image-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RGB_SPECTRA_IMAGE_INL_HPP_
#define _REFLECT_RGB_SPECTRA_IMAGE_INL_HPP_

#include "rgb_spectra_image.hpp"
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void RgbSpectraImage::addRgbContribution(
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  const std::size_t index = widthResolution() * y + x;
  auto& rgb = buffer_[index];
  rgb[0] += contribution.intensity(2);
  rgb[1] += contribution.intensity(1);
  rgb[2] += contribution.intensity(0);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void addRgbContribution(
    SpectraImageInterface* image,
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  auto rgb_image = cast<RgbSpectraImage*>(image);
  rgb_image->addRgbContribution(x, y, contribution);
}

} // namespace reflect

#endif // _REFLECT_RGB_SPECTRA_IMAGE_INL_HPP_
