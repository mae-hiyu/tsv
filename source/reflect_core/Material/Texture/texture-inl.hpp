/*!
  \file texture-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_TEXTURE_INL_HPP_
#define _REFLECT_TEXTURE_INL_HPP_

#include "texture.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
#include "zisc/error.hpp"
// Reflect
#include "checkerboard_texture.hpp"
#include "image_texture.hpp"
#include "reflect_config.hpp"
#include "unicolor_texture.hpp"
#include "value_texture.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> Texture::spectraValue(
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths) const
{
  SampledSpectra<kSampleSize> spectra{wavelengths};

  const auto texture_type = type();
  switch (texture_type) {
   case TextureType::Value:
    spectra = getSpectraValue(this, coordinate, wavelengths);
    break;
   case TextureType::Unicolor:
    spectra = getUnicolorSpectraValue(this, coordinate, wavelengths);
    break;
   case TextureType::Checkerboard:
    spectra = getCheckerboardSpectraValue(this, coordinate, wavelengths);
    break;
   case TextureType::Image:
    spectra = getImageSpectraValue(this, coordinate, wavelengths);
    break;
   default:
    zisc::raiseError("TextureError: spectraValue method is not implemented.");
    break;
  }
  return spectra;
}

} // namespace reflect

#endif // _REFLECT_TEXTURE_INL_HPP_
