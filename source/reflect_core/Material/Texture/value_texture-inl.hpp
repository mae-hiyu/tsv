/*!
  \file value_texture-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_VALUE_TEXTURE_INL_HPP_
#define _REFLECT_VALUE_TEXTURE_INL_HPP_

#include "value_texture.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

// Forward declaration
template <std::size_t> class WavelengthSamples;

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
double ValueTexture::uniqueValue() const
{
  return value_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> getSpectraValue(
    const Texture* texture,
    const Point2& /* coordinate */,
    const WavelengthSamples<kSampleSize>& wavelengths)
{
  auto value_texture = cast<const ValueTexture*>(texture);
  return SampledSpectra<kSampleSize>{wavelengths, value_texture->uniqueValue()};
}

} // namespace reflect

#endif // _REFLECT_VALUE_TEXTURE_INL_HPP_
