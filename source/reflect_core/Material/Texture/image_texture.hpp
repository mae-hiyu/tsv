/*!
  \file image_texture.hpp
  \author takemura
  */

#ifndef _REFLECT_IMAGE_TEXTURE_HPP_
#define _REFLECT_IMAGE_TEXTURE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/spectral_distribution.hpp"

// Forward declaration
class QImage;
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
template <std::size_t> class SampledSpectra;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
class ImageTexture : public Texture
{
 public:
  //! Create a image texture
  ImageTexture(const ColorSystem& color_system,
               const QSettings& settings, 
               const QString& prefix);


  //! Evaluate a float value at the coordinate
  double floatValue(const Point2& coordinate) const override;

  //! Evaluate spectra at the coordinate
  template <std::size_t kSampleSize>
  SampledSpectra<kSampleSize> imageSpectraValue(
      const Point2& coordinate,
      const WavelengthSamples<kSampleSize>& wavelength) const;

  //! Return the image texture type
  TextureType type() const override;

 private:
  //! Initialize
  void initialize(const ColorSystem& color_system,
                  const QSettings& settings, 
                  const QString& prefix);

  //! Set color
  void setColor(const ColorSystem& color_system,
                const QImage& image, 
                const double gamma);


  std::size_t width_resolution_;
  double width_,
         height_;
  std::vector<std::size_t> color_index_;
  std::vector<double> float_table_;
  std::vector<SpectralDistribution> spectra_table_;
};

//! \} Material

} // namespace reflect

#include "image_texture-inl.hpp"

#endif // _REFLECT_IMAGE_TEXTURE_HPP_
