/*!
  \file surface_scattering_model.cpp
  \author takemura
  */

#include "surface_model.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "multilayer_thin_film_surface.hpp"
#include "reflect_config.hpp"
#include "rough_dielectric_surface.hpp"
#include "rough_conductor_surface.hpp"
#include "smooth_conductor_surface.hpp"
#include "smooth_dielectric_surface.hpp"
#include "smooth_diffuse_surface.hpp"
#include "Color/spectral_distribution.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

// Forward declaration
class Texture;

/*!
  \details
  No detailed.
  */
SpectralDistribution SurfaceModel::reflectance() const
{
  const int t = cast<int>(type());
  zisc::raiseError("SurfaceModelError: (type=", t,
                   ") Get reflectance method is not implemented.");
  return SpectralDistribution{};
}

/*!
  \details
  No detailed.
  */
UniquePointer<SurfaceModel> makeSurface(
    const QSettings& settings,
    const QString& prefix,
    const std::vector<const Texture*>& texture_list)
{
  SurfaceModel* surface_scattering = nullptr;

  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::smooth_diffuse_surface):
    surface_scattering = new SmoothDiffuseSurface{settings, prefix, texture_list};
    break;
   case zisc::toHash32(keyword::smooth_dielectric_surface):
    surface_scattering = new SmoothDielectricSurface{settings, prefix};
    break;
   case zisc::toHash32(keyword::smooth_conductor_surface):
    surface_scattering = new SmoothConductorSurface{settings, prefix};
    break;
   case zisc::toHash32(keyword::multilayer_thin_film_surface):
    surface_scattering = new MultilayerThinFilmSurface{settings, prefix};
    break;
   case zisc::toHash32(keyword::rough_dielectric_surface):
    surface_scattering = new RoughDielectricSurface{settings, prefix, texture_list};
    break;
   case zisc::toHash32(keyword::rough_conductor_surface):
    surface_scattering = new RoughConductorSurface{settings, prefix, texture_list};
    break;
   default:
    zisc::raiseError("SurfaceError: Unsupported type is specified.");
    break;
  }

  return UniquePointer<SurfaceModel>{surface_scattering};
}

} // namespace reflect
