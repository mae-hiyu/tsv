/*!
  \file spectra_image-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECTRA_IMAGE_INL_HPP_
#define _REFLECT_SPECTRA_IMAGE_INL_HPP_

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
void SpectraImage::addSpectraContribution(
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  const std::size_t pixel_index = widthResolution() * y + x;
  auto& pixel = buffer_[pixel_index];
  for (std::size_t i = 0; i < kSampleSize; ++i) {
    const std::size_t index = getIndex(contribution.wavelength(i));
    pixel[index] += contribution.intensity(i);
  }
}

template <std::size_t kSampleSize> inline
void XYZSpectraImage::addXYZSpectraContribution(
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  const std::size_t pixel_index = widthResolution() * y + x;
  auto& xpixel = xbuffer_[pixel_index];
  auto& ypixel = ybuffer_[pixel_index];
  auto& zpixel = zbuffer_[pixel_index];
  for (std::size_t i = 0; i < kXYZSampleSize; ++i) {
      const std::size_t xindex = getIndex(contribution.wavelength(i));
      const std::size_t yindex = getIndex(contribution.wavelength(i + kXYZSampleSize));
      const std::size_t zindex = getIndex(contribution.wavelength(i + kXYZSampleSize*2));
      xpixel[xindex] += contribution.intensity(i);
      ypixel[yindex] += contribution.intensity(i + kXYZSampleSize);
      zpixel[zindex] += contribution.intensity(i + kXYZSampleSize*2);    
  }
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void addSpectraContribution(
    SpectraImageInterface* image,
    const std::size_t x,
    const std::size_t y,
    const SampledSpectra<kSampleSize>& contribution)
{
  auto spectra_image = cast<SpectraImage*>(image);
  spectra_image->addSpectraContribution(x, y, contribution);
}

template <std::size_t kSampleSize> inline
void addXYZSpectraContribution(
  SpectraImageInterface* image,
  const std::size_t x,
  const std::size_t y,
  const SampledSpectra<kSampleSize>& contribution
) {
  auto spectra_image = cast<XYZSpectraImage*>(image);
  spectra_image->addXYZSpectraContribution(x,y, contribution);
}


} // namespace reflect

#endif // _REFLECT_SPECTRA_IMAGE_INL_HPP_
