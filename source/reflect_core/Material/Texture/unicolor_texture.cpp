/*!
  \file unicolor_texture.cpp
  \author takemura
  */

#include "unicolor_texture.hpp"
// Standard C++ library
#include <cstddef>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/spectral_distribution.hpp"
#include "RendererBase/color_system.hpp"
#include "Data/wavelength_samples.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
UnicolorTexture::UnicolorTexture(const ColorSystem& color_system,
                                 const QSettings& settings,
                                 const QString& prefix)
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
double UnicolorTexture::floatValue(const Point2& /* coordinate */) const
{
  return float_value_;
}

/*!
  \details
  No detailed.
  */
TextureType UnicolorTexture::type() const
{
  return TextureType::Unicolor;
}

/*!
  \details
  No detailed.
  */
SpectralDistribution UnicolorTexture::weight() const
{
  return spectra_value_;
}

/*!
  \details
  No detailed.
  */
void UnicolorTexture::initialize(const ColorSystem& color_system,
                                 const QSettings& settings,
                                 const QString& prefix)
{
  const auto key = prefix + "/" + keyword::color;
  spectra_value_ = makeReflectiveDistribution(color_system, settings, key);
  float_value_ = 
      zisc::clamp(0.0, 1.0, spectra_value_.toReflectiveXyz(color_system).y());
}

} // namespace reflect
