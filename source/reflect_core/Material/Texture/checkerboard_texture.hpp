/*!
  \file checkerboard_texture.hpp
  \author takemura
  */

#ifndef _REFLECT_CHECKERBOARD_TEXTURE_HPP_
#define _REFLECT_CHECKERBOARD_TEXTURE_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/spectral_distribution.hpp"

// Forward declaration
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
class CheckerboardTexture : public Texture
{
 public:
  //! Create a checkerboard texture
  CheckerboardTexture(const ColorSystem& color_system,
                      const QSettings& settings, 
                      const QString& prefix);


  //! Evaluate a float value at the coordinate
  double floatValue(const Point2& coordinate) const override;

  //! Evaluate spectra at the coordinate
  template <std::size_t kSampleSize>
  SampledSpectra<kSampleSize> checkerboardSpectraValue(
      const Point2& coordinate,
      const WavelengthSamples<kSampleSize>& wavelengths) const;

  //! Return the checkerboard texture type
  TextureType type() const override;

 private:
  //! Initialize
  void initialize(const ColorSystem& color_system,
                  const QSettings& settings, 
                  const QString& prefix);


  double width_,
         height_;
  double float_value_[2];
  SpectralDistribution spectra_value_[2];
};

//! \} Material

} // namespace reflect

#include "checkerboard_texture-inl.hpp"

#endif // _REFLECT_CHECKERBOARD_TEXTURE_HPP_
