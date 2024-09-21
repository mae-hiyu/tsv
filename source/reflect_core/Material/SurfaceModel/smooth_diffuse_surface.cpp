/*!
  \file smooth_diffuse_surface.cpp
  \author takemura
  */

#include "smooth_diffuse_surface.hpp"
// Standard C++ library
#include <vector>
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "surface_model.hpp"
#include "Material/Texture/texture.hpp"

namespace reflect {

// Forward declaration
class SpectralDistribution;

/*!
  \details
  No detailed.
  */
SmoothDiffuseSurface::SmoothDiffuseSurface(
    const QSettings& settings,
    const QString& prefix,
    const std::vector<const Texture*>& texture_list)
{
  initialize(settings, prefix, texture_list);
}

/*!
  \details
  No detailed.
  */
SpectralDistribution SmoothDiffuseSurface::reflectance() const
{
  return reflectance_->weight();
}

/*!
  \details
  No detailed.
  */
SurfaceType SmoothDiffuseSurface::type() const
{
  return SurfaceType::SmoothDiffuse;
}

/*!
  \details
  No detailed.
  */
void SmoothDiffuseSurface::initialize(
    const QSettings& settings,
    const QString& prefix,
    const std::vector<const Texture*>& texture_list)
{
  const auto key = prefix + "/" + keyword::reflectance;
  reflectance_ = getTexture(settings, key, texture_list);
}

} // namespace reflect
