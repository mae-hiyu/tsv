/*!
  \file smooth_conductor_surface.cpp
  \author takemura
  */

#include "smooth_conductor_surface.hpp"
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "keyword.hpp"
#include "fresnel.hpp"
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
SmoothConductorSurface::SmoothConductorSurface(const QSettings& settings,
                                               const QString& prefix)
{
  initialize(settings, prefix);
}

/*!
  \details
  No detailed.
  */
SurfaceType SmoothConductorSurface::type() const
{
  return SurfaceType::SmoothConductor;
}

/*!
  \details
  No detailed.
  */
void SmoothConductorSurface::initialize(const QSettings& settings, 
                                        const QString& prefix)
{
  QString key{prefix + "/" + keyword::exterior_refractive_index};
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
