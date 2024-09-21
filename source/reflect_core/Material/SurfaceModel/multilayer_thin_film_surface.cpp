/*!
  \file multilayer_thin_film_surface.cpp
  \author takemura
  */

#include "multilayer_thin_film_surface.hpp"
// Standard C++ library
#include <array>
#include <cmath>
#include <complex>
#include <cstddef>
#include <iterator>
#include <limits>
#include <vector>
// Qt
#include <QString>
#include <QSettings>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
#include "zisc/unit.hpp"
// Reflect
#include "fresnel.hpp"
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "surface_model.hpp"
#include "Color/spectral_distribution.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
MultilayerThinFilmSurface::MultilayerThinFilmSurface(const QSettings& settings,
                                                     const QString& prefix)
{
  initialize(settings, prefix);
}

/*!
  \details
  No detailed.
  */
SurfaceType MultilayerThinFilmSurface::type() const
{
  return SurfaceType::MultilayerThinFilms;
}

/*!
  \details
  No detailed.
  */
void calculateConductorReflectance(const double theta,
                                   const std::complex<double>& n,
                                   std::complex<double>& reflectance_p,
                                   std::complex<double>& reflectance_s)
{
    const double cos_theta = std::cos(theta);
    const double t1 = std::norm(n);
    const double t2 = cos_theta * cos_theta;
    const double t3 = t1 * t2;
    const double t4 = 2.0 * n.real() * cos_theta;
    const double t5 = t4 + 1.0;
    const double t6 = t2 + t4;

    reflectance_p = std::complex<double>{(t3 - t5) / (t3 + t5), 0.0};
    reflectance_s = std::complex<double>{(t1 - t6) / (t1 + t6), 0.0};
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmSurface::calculateCompositeProperties(
    const double theta_i,
    const std::size_t lambda,
    const std::vector<Layer>& multilayer,
    const std::size_t number,
    std::complex<double>& reflectance_p,
    std::complex<double>& reflectance_s) const
{
  const std::size_t index = getIndex(lambda);
  const double wavelength = cast<double>(lambda);

  const auto& n_i = multilayer[number].complex_refractive_index_[index];
  const auto& n_t = multilayer[number + 1].complex_refractive_index_[index];

  if (isPerfectReflection(theta_i, n_i, n_t)) {
    if (n_t.imag() != 0.0)
      calculateConductorReflectance(theta_i, n_t, reflectance_p, reflectance_s);
    return;
  }

  if (number != multilayer.size() - 2) {
    const double theta_t = calculateRefractionAngle(theta_i, n_i, n_t);
    calculateCompositeProperties(theta_t, lambda, multilayer, number + 1,
                                 reflectance_p, reflectance_s);

    const auto r_p = 
        calculateParallelBoundaryReflectance(n_i, n_t, theta_i, theta_t);
    const auto r_s =
        calculatePerpendicularBoundaryReflectance(n_i, n_t, theta_i, theta_t);

    const double thickness = multilayer[number + 1].thickness_;
    const auto phi = calculatePhaseDifference(wavelength, thickness, n_t, theta_t);
    reflectance_p = calculateCompositeReflectance(reflectance_p, r_p, phi);
    reflectance_s = calculateCompositeReflectance(reflectance_s, r_s, phi);
  }
  else {
    calculateConductorReflectance(theta_i, n_t, reflectance_p, reflectance_s);
  }
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmSurface::initialize(const QSettings& settings,
                                           const QString& prefix)
{
  const auto multilayer = makeMultilayer(settings, prefix);
  setCompositeProperties(multilayer);
}

/*!
  \details
  No detailed.
  */
auto MultilayerThinFilmSurface::makeExteriorMediumLayer(
    const QSettings& settings,
    const QString& prefix) -> Layer
{
  Layer layer;
  layer.thickness_ = std::numeric_limits<double>::max();

  // Refractive index
  QString key{prefix + "/" + keyword::exterior_refractive_index};
  const auto refractive_index = makeSpectra(settings, key);
  for (std::size_t index = 0; index < kSpectraSize; ++index)
    layer.complex_refractive_index_[index].real(refractive_index[index]);

  return layer;
}

/*!
  \details
  No detailed.
  */
auto MultilayerThinFilmSurface::makeInteriorMediumLayer(
    const QSettings& settings,
    const QString& prefix) -> Layer
{
  Layer layer;
  layer.thickness_ = std::numeric_limits<double>::max();

  // Refractive index
  QString key{prefix + "/" + keyword::interior_refractive_index};
  const auto refractive_index = makeSpectra(settings, key);
  for (std::size_t index = 0; index < kSpectraSize; ++index)
    layer.complex_refractive_index_[index].real(refractive_index[index]);

  // Extinction coefficient
  key = prefix + "/" + keyword::interior_extinction;
  const auto extinction = makeSpectra(settings, key);
  for (std::size_t index = 0; index < kSpectraSize; ++index)
    layer.complex_refractive_index_[index].imag(extinction[index]);

  return layer;
}

/*!
  \details
  No detailed.
  */
auto MultilayerThinFilmSurface::makeMultilayer(const QSettings& settings,
                                               const QString& prefix)
    -> std::vector<Layer>
{
  std::vector<Layer> multilayer;

  const int count = value<int>(settings, prefix + "/" + keyword::count);
  const std::size_t size = cast<std::size_t>(count) + 2;
  multilayer.reserve(size);

  multilayer.emplace_back(makeExteriorMediumLayer(settings, prefix));
  for (int index = 0; index < count; ++index) {
    const auto item_id = (prefix + "/" + keyword::item).arg((count - 1) - index);
    if (!value<bool>(settings, item_id + "/" + keyword::enabled))
      continue;
    multilayer.emplace_back(makeThinFilmLayer(settings, item_id));
  }
  multilayer.emplace_back(makeInteriorMediumLayer(settings, prefix));

  return multilayer;
}

/*!
  \details
  No detailed.
  */
auto MultilayerThinFilmSurface::makeThinFilmLayer(
    const QSettings& settings,
    const QString& prefix) -> Layer
{
  Layer layer;

  // Thickness
  QString key{prefix + "/" + keyword::thickness};
  layer.thickness_ = value<double>(settings, key);

  // Refractive index
  key = prefix + "/" + keyword::refractive_index;
  const auto refractive_index = makeSpectra(settings, key);
  for (std::size_t index = 0; index < kSpectraSize; ++index)
    layer.complex_refractive_index_[index].real(refractive_index[index]);

  // Extinction coefficient
  key = prefix + "/" + keyword::is_conductor;
  if (value<bool>(settings, key)) {
    key = prefix + "/" + keyword::extinction_coefficient;
    const auto extinction = makeSpectra(settings, key);
    for (std::size_t index = 0; index < kSpectraSize; ++index)
      layer.complex_refractive_index_[index].imag(extinction[index]);
  }

  return layer;
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmSurface::setCompositeProperties(
    const std::vector<Layer>& multilayer)
{
  for (std::size_t i = 0; i < kN - 1; ++i) {
    const std::size_t angle = kDeltaAngle * i;
    const double theta = zisc::toRadian(cast<double>(angle));
    for (std::size_t index = 0; index < kSpectraSize; ++index) {
      const std::size_t lambda = getWavelength(index);
      std::complex<double> reflectance_p{1.0, 0.0},
                           reflectance_s{1.0, 0.0};
      calculateCompositeProperties(theta, lambda, multilayer, 0,
                                   reflectance_p, reflectance_s);
      const auto r = 0.5 * (std::norm(reflectance_p) + std::norm(reflectance_s));
      reflectance_[i].setByWavelength(lambda, zisc::clamp(0.0, 1.0, r));
    }
  }
  reflectance_[kN - 1].fill(1.0);
}

} // namespace reflect
