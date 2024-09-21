/*!
  \file value_texture.hpp
  \author takemura
  */

#ifndef _REFLECT_VALUE_TEXTURE_HPP_
#define _REFLECT_VALUE_TEXTURE_HPP_

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
class ValueTexture : public Texture
{
 public:
  //! Create a value texture
  ValueTexture(const ColorSystem& color_system,
               const QSettings& settings, 
               const QString& prefix);

  //! Return the unique float value
  double uniqueValue() const;

  //! Evaluate a float value at the coordinate
  double floatValue(const Point2& coordinate) const override;

  //! Return the value texture type
  TextureType type() const override;

  //! Return the spectral weight
  SpectralDistribution weight() const override;
  
 private:
  //! Initialize
  void initialize(const ColorSystem& color_system,
                  const QSettings& settings, 
                  const QString& prefix);


  double value_;
};

//! \} Material

} // namespace reflect

#include "value_texture-inl.hpp"

#endif // _REFLECT_VALUE_TEXTURE_HPP_
