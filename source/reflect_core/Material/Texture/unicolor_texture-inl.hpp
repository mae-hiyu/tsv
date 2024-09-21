/*!
  \file unicolor_texture-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_UNICOLOR_TEXTURE_INL_HPP_
#define _REFLECT_UNICOLOR_TEXTURE_INL_HPP_

#include "unicolor_texture.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/spectral_distribution.hpp"
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
SampledSpectra<kSampleSize> UnicolorTexture::unicolorSpectraValue(
    const Point2& /* coordinate */,
    const WavelengthSamples<kSampleSize>& wavelengths) const
{
  return sample(spectra_value_, wavelengths);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> getUnicolorSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths)
{
  auto unicolor_texture = cast<const UnicolorTexture*>(texture);
  return unicolor_texture->unicolorSpectraValue(coordinate, wavelengths);
}

} // namespace reflect

#endif // _REFLECT_UNICOLOR_TEXTURE_INL_HPP_
