/*!
  \file multilayer_thin_film_surface-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_MULTILAYER_THIN_FILM_SURFACE_INL_HPP_
#define _REFLECT_MULTILAYER_THIN_FILM_SURFACE_INL_HPP_

#include "multilayer_thin_film_surface.hpp"
// Standard C++ library
#include <cstddef>
#include <complex>
// Zisc
#include "zisc/math.hpp"
#include "zisc/unit.hpp"
// Reflect
#include "fresnel.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/intersection_info.hpp"
#include "Data/wavelength_samples.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Material/Bxdf/specular_brdf.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto MultilayerThinFilmSurface::makeSpecularBrdf(
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& /* sampler */,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  using Brdf = SpecularBrdf<kSampleSize>;

  const auto& normal = intersection.normal();
  const double cos_theta_i = -zisc::dot(normal, *vin);
  REFLECT_CHECK_NON_ZERO_FLOAT(cos_theta_i);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta_i);

  // Calculate reflection direction 
  const auto vout = getFresnelReflectionDirection(*vin, normal, cos_theta_i);

  // Interpolate reflectance
  constexpr double delta_theta = zisc::toRadian(cast<double>(kDeltaAngle));
  constexpr double inverse_delta_theta = 1.0 / delta_theta;
  const double theta = std::acos(cos_theta_i);
  const double length = theta * inverse_delta_theta;
  const std::size_t index = cast<std::size_t>(length);
  const double a = length - cast<double>(index);
  const auto r1 = sample(reflectance_[index    ], wavelengths);
  const auto r2 = sample(reflectance_[index + 1], wavelengths);
  const auto reflectance = r1 + a * (r2 - r1);

  auto brdf = memory_pool.allocate<Brdf>(normal, vout, cos_theta_i, reflectance);
  return ShaderPointer<kSampleSize>{brdf};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SurfaceModel::ShaderPointer<kSampleSize> makeThinFilmSpecularBrdf(
    const SurfaceModel* surface,
    const Vector3* vin,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool)
{
  auto thin_film_surface = cast<const MultilayerThinFilmSurface*>(surface);
  return thin_film_surface->makeSpecularBrdf(vin,
                                             intersection,
                                             wavelengths,
                                             sampler,
                                             memory_pool);
}

/*!
  \details
  No detailed.
  */
inline
std::complex<double> calculateParallelBoundaryReflectance(
    const std::complex<double>& n_i,
    const std::complex<double>& n_t,
    const double theta_i,
    const double theta_t)
{
  const double cos_theta_i = std::cos(theta_i);
  const double cos_theta_t = std::cos(theta_t);
  return (n_t * cos_theta_i - n_i * cos_theta_t) / 
         (n_t * cos_theta_i + n_i * cos_theta_t);
}

/*!
  \details
  No detailed.
  */
inline
std::complex<double> calculatePerpendicularBoundaryReflectance(
    const std::complex<double>& n_i,
    const std::complex<double>& n_t,
    const double theta_i,
    const double theta_t)
{
  const double cos_theta_i = std::cos(theta_i);
  const double cos_theta_t = std::cos(theta_t);
  return (n_i * cos_theta_i - n_t * cos_theta_t) / 
         (n_i * cos_theta_i + n_t * cos_theta_t);
}

/*!
  \details
  No detailed.
  */
inline
std::complex<double> calculateCompositeReflectance(
    const std::complex<double>& reflectance,
    const std::complex<double>& r,
    const std::complex<double>& phi)
{
  constexpr std::complex<double> i{0.0, 1.0};
  const auto e2 = std::exp(2.0 * i * phi);
  return (r + reflectance * e2) / (1.0 + r * reflectance * e2);
}

/*!
  \details
  No detailed.
  */
inline
std::complex<double> calculatePhaseDifference(const double wavelength,
                                              const double thickness,
                                              const std::complex<double>& n,
                                              const double theta)
{
  const double cos_theta = std::cos(theta);
  return (2.0 * zisc::kPi * thickness * cos_theta / wavelength) * n;
}

/*!
  \details
  No detailed.
  */
inline
double calculateRefractionAngle(const double theta_i,
                                const std::complex<double>& n_i,
                                const std::complex<double>& n_t)
{
  return std::asin((n_i.real() / n_t.real()) * std::sin(theta_i));
}

/*!
  \details
  No detailed.
  */
inline
bool isPerfectReflection(const double theta_i,
                         const std::complex<double>& n_i,
                         const std::complex<double>& n_t)
{
  return (n_i.real() > n_t.real()) && 
         (theta_i >= std::asin(n_t.real() / n_i.real()));
}

} // namespace reflect

#endif // _REFLECT_MULTILAYER_THIN_FILM_SURFACE_INL_HPP_
