/*!
  \file value_texture.cpp
  \author takemura
  */

#include "value_texture.hpp"
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/spectral_distribution.hpp"
#include "RendererBase/color_system.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ValueTexture::ValueTexture(const ColorSystem& color_system,
                           const QSettings& settings,
                           const QString& prefix)
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
double ValueTexture::floatValue(const Point2& /* coordinate */) const
{
  return value_;
}

/*!
  \details
  No detailed.
  */
TextureType ValueTexture::type() const
{
  return TextureType::Value;
}

/*!
  \details
  No detailed.
  */
SpectralDistribution ValueTexture::weight() const
{
  SpectralDistribution distribution{};
  distribution.fill(value_);
  return distribution;
}

/*!
  \details
  No detailed.
  */
void ValueTexture::initialize(const ColorSystem& /* color_system */,
                              const QSettings& settings,
                              const QString& prefix)
{
  const auto key = prefix + "/" + keyword::value;
  value_ = value<double>(settings, prefix + "/" + keyword::value);
}

} // namespace reflect
