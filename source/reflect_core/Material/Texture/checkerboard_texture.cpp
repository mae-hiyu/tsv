/*!
  \file checkerboard_texture.cpp
  \author takemura
  */

#include "checkerboard_texture.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <limits>
#include <vector>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Color/xyz_color.hpp"
#include "LinearAlgebra/point.hpp"
#include "RendererBase/color_system.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
CheckerboardTexture::CheckerboardTexture(const ColorSystem& color_system,
                                         const QSettings& settings,
                                         const QString& prefix)
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
double CheckerboardTexture::floatValue(const Point2& coordinate) const
{
  const auto x = cast<std::size_t>(coordinate[0] * width_);
  const auto y = cast<std::size_t>(coordinate[1] * height_);

  return (((x ^ y) & 1) == 1) ? float_value_[1] : float_value_[0];
}

/*!
  \details
  No detailed.
  */
TextureType CheckerboardTexture::type() const
{
  return TextureType::Checkerboard;
}

/*!
  \details
  No detailed.
  */
void CheckerboardTexture::initialize(const ColorSystem& color_system,
                                     const QSettings& settings,
                                     const QString& prefix)
{
  const auto width = value<std::size_t>(settings, prefix + "/" + keyword::width);
  width_ = cast<double>(width) - std::numeric_limits<double>::epsilon();

  const auto height = value<std::size_t>(settings, prefix + "/" + keyword::height);
  height_ = cast<double>(height) - std::numeric_limits<double>::epsilon();

  auto key = prefix + "/" + keyword::color1;
  spectra_value_[0] = makeReflectiveDistribution(color_system, settings, key);
  key = prefix + "/" + keyword::color2;
  spectra_value_[1] = makeReflectiveDistribution(color_system, settings, key);

  float_value_[0] = 
      zisc::clamp(0.0, 1.0, spectra_value_[0].toReflectiveXyz(color_system).y());
  float_value_[1] = 
      zisc::clamp(0.0, 1.0, spectra_value_[1].toReflectiveXyz(color_system).y());
}

} // namespace reflect
