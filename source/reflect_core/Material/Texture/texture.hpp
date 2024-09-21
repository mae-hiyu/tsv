/*!
  \file texture.hpp
  \author takemura
  */

#ifndef _REFLECT_TEXTURE_HPP_
#define _REFLECT_TEXTURE_HPP_

// Standard C+ library
#include <cstddef>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
template <std::size_t> class SampledSpectra;
class SpectralDistribution;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
enum class TextureType : int
{
  Value = 0,
  Unicolor,
  Checkerboard,
  Image
};

/*!
  \details
  No detailed.
  */
class Texture
{
 public:
  //! Dummy function
  virtual ~Texture() {}


  //! Evaluate a float value at the texture coordinate
  virtual double floatValue(const Point2& coordinate) const = 0;

  //! Evaluate spectra at the texture coordinate
  template <std::size_t kSampleSize>
  SampledSpectra<kSampleSize> spectraValue(
      const Point2& coordinate,
      const WavelengthSamples<kSampleSize>& wavelengths) const;

  //! Return the texture type
  virtual TextureType type() const = 0;

  //! Return the spectral weight
  virtual SpectralDistribution weight() const;
};

//! Get unicolor spectra
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> getSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths);

//! Get unicolor spectra
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> getUnicolorSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths);

//! Get unicolor spectra
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> getCheckerboardSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths);

//! Get unicolor spectra
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> getImageSpectraValue(
    const Texture* texture,
    const Point2& coordinate,
    const WavelengthSamples<kSampleSize>& wavelengths);

//! Make a texture
UniquePointer<Texture> makeTexture(const ColorSystem& color_system,
                                   const QSettings& settings,
                                   const QString& prefix);

//! Get a texture
const Texture* getTexture(const QSettings& settings,
                          const QString& prefix,
                          const std::vector<const Texture*>& texture_list);

//! \} Material

} // namespace reflect

#include "texture-inl.hpp"

#endif // _REFLECT_TEXTURE_HPP_
