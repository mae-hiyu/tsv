/*!
  \file rough_dielectric_surface.cpp
  \author takemura
  */

#include "rough_dielectric_surface.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
#include <vector>
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "fresnel.hpp"
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "surface_model.hpp"
#include "Color/spectral_distribution.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
RoughDielectricSurface::RoughDielectricSurface(
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
SurfaceType RoughDielectricSurface::type() const
{
  return SurfaceType::RoughDielectric;
}

/*!
  \details
  No detailed.
  */
void RoughDielectricSurface::initialize(
    const QSettings& settings,
    const QString& prefix,
    const std::vector<const Texture*>& texture_list)
{
  auto key = prefix + "/" + keyword::roughness;
  roughness_ = getTexture(settings, key, texture_list);

  key = prefix + "/" + keyword::exterior_refractive_index;
  const auto n1 = makeSpectra(settings, key);

  key = prefix + "/" + keyword::interior_refractive_index;
  const auto n2 = makeSpectra(settings, key);

  eta_ = n2 / n1;
  REFLECT_CHECK_VALID_FLOAT(eta_);
  REFLECT_CHECK_NON_ZERO_FLOAT(eta_);
}

} // namespace reflect
