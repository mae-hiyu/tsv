/*!
  \file checkerboard_texture-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_CHECKERBOARD_TEXTURE_INL_HPP_
#define _REFLECT_CHECKERBOARD_TEXTURE_INL_HPP_

#include "checkerboard_texture.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/spectral_distribution.hpp"
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
SampledSpectra<kSampleSize> CheckerboardTexture::checkerboardSpectraValue(
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths) const
{
  const auto x = cast<std::size_t>(coordinate[0] * width_);
  const auto y = cast<std::size_t>(coordinate[1] * height_);

  return (((x ^ y) & 1) == 1)
      ? sample(spectra_value_[1], wavelengths)
      : sample(spectra_value_[0], wavelengths);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> getCheckerboardSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths)
{
  auto checkerboard_texture = cast<const CheckerboardTexture*>(texture);
  return checkerboard_texture->checkerboardSpectraValue(coordinate, wavelengths);
}

} // namespace reflect

#endif // _REFLECT_CHECKERBOARD_TEXTURE_INL_HPP_
