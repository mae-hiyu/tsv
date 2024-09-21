/*!
  \file rough_conductor_surface.cpp
  \author takemura
  */

#include "rough_conductor_surface.hpp"
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
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
RoughConductorSurface::RoughConductorSurface(
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
SurfaceType RoughConductorSurface::type() const
{
  return SurfaceType::RoughConductor;
}

/*!
  \details
  No detailed.
  */
void RoughConductorSurface::initialize(
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

  key = prefix + "/" + keyword::interior_extinction;
  const auto k2 = makeSpectra(settings, key);

  const auto eta = n2 / n1;
  const auto eta_k = k2 / n1;
  r0_ = calculateFresnelConductorReflectance0(eta, eta_k);
}

} // namespace reflect
