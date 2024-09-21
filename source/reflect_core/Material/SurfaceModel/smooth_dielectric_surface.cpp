/*!
  \file smooth_dielectric_surface.cpp
  \author takemura
  */

#include "smooth_dielectric_surface.hpp"
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
SmoothDielectricSurface::SmoothDielectricSurface(const QSettings& settings,
                                                 const QString& prefix)
{
  initialize(settings, prefix);
}

/*!
  \details
  No detailed.
  */
SurfaceType SmoothDielectricSurface::type() const
{
  return SurfaceType::SmoothDielectric;
}

/*!
  \details
  No detailed.
  */
void SmoothDielectricSurface::initialize(const QSettings& settings,
                                         const QString& prefix)
{
  auto key = prefix + "/" + keyword::exterior_refractive_index;
  const auto n1 = makeSpectra(settings, key);

  key = prefix + "/" + keyword::interior_refractive_index;
  const auto n2 = makeSpectra(settings, key);

  eta_ = n2 / n1;
  REFLECT_CHECK_VALID_FLOAT(eta_);
  REFLECT_CHECK_NON_ZERO_FLOAT(eta_);
}

} // namespace reflect
