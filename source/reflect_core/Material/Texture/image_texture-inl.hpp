/*!
  \file image_texture-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_IMAGE_TEXTURE_INL_HPP_
#define _REFLECT_IMAGE_TEXTURE_INL_HPP_

#include "image_texture.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "texture.hpp"
#include "LinearAlgebra/point.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

// Forward declaration
template <std::size_t> class WavelengthSamples;

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> ImageTexture::imageSpectraValue(
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths) const
{
  const auto x = cast<std::size_t>(coordinate[0] * width_);
  const auto y = cast<std::size_t>(coordinate[1] * height_);
  const std::size_t index = width_resolution_ * y + x;
  return sample(spectra_table_[color_index_[index]], wavelengths);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> getImageSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths)
{
  auto image_texture = cast<const ImageTexture*>(texture);
  return image_texture->imageSpectraValue(coordinate, wavelengths);
}

} // namespace reflect

#endif // _REFLECT_IMAGE_TEXTURE_INL_HPP_
