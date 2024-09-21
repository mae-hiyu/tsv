/*!
  \file fresnel-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_FRESNEL_INL_HPP_
#define _REFLECT_FRESNEL_INL_HPP_

#include "fresnel.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <utility>
// Zisc
#include "zisc/math.hpp"
// Reflect
#include "Color/spectral_distribution.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/floating_point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
SpectralDistribution calculateFresnelConductorReflectance0(
    const SpectralDistribution& eta,
    const SpectralDistribution& eta_k)
{
  SpectralDistribution one;
  one.fill(1.0);

  const auto eta2_a = (eta - one) * (eta - one);
  const auto eta2_b = (eta + one) * (eta + one);
  const auto etak2 = eta_k * eta_k;
  auto r0 = (eta2_a + etak2) / (eta2_b + etak2);
  r0.clamp(0.0, 1.0);
  return r0;
}

/*!
  \details
  No detailed.
  */
inline
Vector3 getFresnelReflectionDirection(const Vector3& vin, 
                                      const Vector3& normal,
                                      const double cos_theta)
{
  const auto vout = vin + (2.0 * cos_theta) * normal;
  REFLECT_CHECK_UNIT_VECTOR(vout);
  return vout;
}

/*!
  \details
  No detailed.
  */
inline
Vector3 getFresnelRefractionDirection(const Vector3& vin,
                                      const Vector3& normal,
                                      const double cos_theta,
                                      const double n,
                                      const double g)
{
  const auto vout = (vin + (cos_theta - g) * normal) * (1.0 / n);
  REFLECT_CHECK_UNIT_VECTOR(vout);
  return vout;
}

/*!
  \details
  No detailed.
  */
inline
std::pair<bool, double> evaluateFresnelG(const double n, const double cos_theta)
{
  const double g2 = n * n + cos_theta * cos_theta - 1.0;
  return (g2 < 0.0) 
      ? std::make_pair(false, 0.0) 
      : std::make_pair(true, zisc::sqrt(g2));
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledSpectra<kSampleSize> solveFresnelConductorEquation(
    const double cos_theta,
    const SampledSpectra<kSampleSize>& r0)
{
  const SampledSpectra<kSampleSize> one{r0.wavelengths(), 1.0};
  const double tmp1 = (1.0 - cos_theta);
  const double tmp2 = tmp1 * tmp1;
  const double tmp3 = tmp1 * tmp2 * tmp2;
  const auto reflectance = r0 + (one - r0) * tmp3;
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(reflectance);
  return reflectance;
}

/*!
  \details
  No detailed.
  */
//inline
//SampledSpectra solveFresnelConductorEquation(const double cos_theta,
//                                             const SampledSpectra& eta,
//                                             const SampledSpectra& eta_k)
//{
//  const auto eta2 = eta * eta;
//  const auto eta_k2 = eta_k * eta_k;
//  const double cos2_theta = cos_theta * cos_theta;
//  const double sin2_theta = 1.0 - cos2_theta;
//  const double sin4_theta = sin2_theta * sin2_theta;
//
//  const auto tmp1 = eta2 - eta_k2 - sin2_theta;
//  const auto tmp2 = sqrt(tmp1 * tmp1 + 4.0 * eta2 * eta_k2);
//  const auto tmp3 = sqrt(0.5 * (tmp1 + tmp2));
//  const auto tmp4 = (2.0 * cos_theta) * tmp3;
//  const auto tmp5 = tmp4 * sin2_theta;
//  const auto tmp6 = tmp2 * cos2_theta;
//
//  // Solve fresnel conductor equation
//  const auto r_s = (tmp2 + cos2_theta - tmp4) / (tmp2 + cos2_theta + tmp4);
//  const auto r_p = r_s * ((tmp6 + sin4_theta - tmp5) / (tmp6 + sin4_theta + tmp5));
//  const auto reflectance = 0.5 * (r_s + r_p);
//  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(reflectance);
//
//  return reflectance;
//}

/*!
  \details
  No detailed.
  */
inline
double solveFresnelDielectricEquation(const double cos_theta, const double g)
{
  const double a = g + cos_theta,
               b = g - cos_theta;
  const double tmp1 = b / a,
               tmp2 = (cos_theta * a - 1.0) / (cos_theta * b + 1.0);
  const double reflectance = 0.5 * tmp1 * tmp1 * (1.0 + tmp2 * tmp2);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(reflectance);
  return reflectance;
}

} // namespace refelct

#endif // _REFLECT_FRESNEL_INL_HPP_
