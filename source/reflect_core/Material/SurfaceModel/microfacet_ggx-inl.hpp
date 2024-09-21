/*!
  \file microfacet_ggx-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_MICROFACET_GGX_INL_HPP_
#define _REFLECT_MICROFACET_GGX_INL_HPP_

#include "microfacet_ggx.hpp"
// Standard C++ library
#include <cstddef>
#include <cmath>
// Zisc
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "microfacet.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/floating_point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> evaluateGgxReflectance(
    const double roughness,
    const Vector3& vin,
    const Vector3& vout,
    const Vector3& normal,
    const SampledSpectra<kSampleSize>& r0,
    const double cos_theta_i,
    const double cos_theta_o)
{
  const auto& wavelengths = r0.wavelengths();

  // Calculate reflection half vector
  const auto m_normal = getMicrofacetReflectionHalfVector(vin, vout, cos_theta_i);

  const double cos_theta_m = zisc::dot(normal, m_normal);
  const double cos_theta_mi = -zisc::dot(m_normal, vin);
  const double cos_theta_mo = cos_theta_mi;

  // Evaluate D
  if (cos_theta_i * cos_theta_mi < 0.0)
    return SampledSpectra<kSampleSize>{wavelengths};
  const double d = evaluateGgxD(roughness, cos_theta_m);

  // Evaluate G2(i, o, m)
  const double g2 = evaluateGgxG2(roughness, cos_theta_i, cos_theta_o,
                                  cos_theta_m, cos_theta_mi, cos_theta_mo);
  if (g2 == 0.0)
    return SampledSpectra<kSampleSize>{wavelengths};

  // Evaluate the fresnel reflectance
  const auto fresnel = solveFresnelConductorEquation(cos_theta_mi, r0);

  const double scale_factor = 4.0 * cos_theta_i * cos_theta_o;

  const auto f = fresnel * (g2 * d / scale_factor);
  REFLECT_CHECK_POSITIVE_FLOAT(f);
  return f;
}

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxD(const double roughness, const double cos_theta_m)
{
  const double a2 = roughness * roughness;
  const double tmp = cos_theta_m * cos_theta_m * (a2 - 1.0) + 1.0;
  const double d = a2 / (zisc::kPi * tmp * tmp);
  REFLECT_CHECK_POSITIVE_FLOAT(d);
  return d;
}

#ifdef _REFLECT_GGX_V_CAVITY_

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxG1(const double /* roughness */,
                     const double cos_theta_omega,
                     const double cos_theta_m,
                     const double cos_theta_momega)
{
  if (cos_theta_momega * cos_theta_omega <= 0.0)
    return 0.0;

  const double g = std::abs(2.0 * cos_theta_m * cos_theta_omega / cos_theta_momega);
  return std::min(1.0, g);
}

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxG2(const double roughness,
                     const double cos_theta_i,
                     const double cos_theta_o,
                     const double cos_theta_m,
                     const double cos_theta_mi,
                     const double cos_theta_mo)
{
  const double g1i = evaluateGgxG1(roughness, cos_theta_i, cos_theta_m, cos_theta_mi);
  const double g1o = evaluateGgxG1(roughness, cos_theta_o, cos_theta_m, cos_theta_mo);
  return (0.0 < cos_theta_o)
      ? std::min(g1i, g1o)
      : std::max(g1i + g1o - 1.0, 0.0);
}

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxWeight(const double roughness,
                         const double cos_theta_i,
                         const double cos_theta_o,
                         const double cos_theta_m,
                         const double cos_theta_mi,
                         const double cos_theta_mo)
{
  const double weight =  evaluateGgxG2(roughness, cos_theta_i, cos_theta_o,
                                       cos_theta_m, cos_theta_mi, cos_theta_mo) /
                         evaluateGgxG1(roughness, cos_theta_i, 
                                       cos_theta_m, cos_theta_mi);
  return zisc::clamp(0.0, 1.0, weight);
}

#else // _REFLECT_GGX_V_CAVITY_

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxG1(const double roughness, 
                     const double cos_theta_omega, 
                     const double /* cos_theta_m */,
                     const double cos_theta_momega)
{
  if (cos_theta_momega * cos_theta_omega <= 0.0)
    return 0.0;

  const double tan_theta2 = 1.0 / (cos_theta_omega * cos_theta_omega) - 1.0;
  return 2.0 / (1.0 + std::sqrt(1.0 + roughness * roughness * tan_theta2));
}

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxG2(const double roughness,
                     const double cos_theta_i,
                     const double cos_theta_o,
                     const double cos_theta_m,
                     const double cos_theta_mi,
                     const double cos_theta_mo)
{
  return evaluateGgxG1(roughness, cos_theta_i, cos_theta_m, cos_theta_mi) *
         evaluateGgxG1(roughness, cos_theta_o, cos_theta_m, cos_theta_mo);
}

/*!
  \details
  No detailed.
  */
inline
double evaluateGgxWeight(const double roughness,
                         const double /* cos_theta_i */,
                         const double cos_theta_o,
                         const double cos_theta_m,
                         const double /* cos_theta_mi */,
                         const double cos_theta_mo)
{
  return evaluateGgxG1(roughness, cos_theta_o, cos_theta_m, cos_theta_mo);
}

/*!
  \details
  No detailed.
  */
//inline
//Vector3 stretchGgxMicrosurface(const double roughness, const Vector3& vin)
//{
//  const Vector3 vin_dash{roughness * vin[0], roughness * vin[1], vin[2]};
//  return vin_dash.normalized();
//}

#endif // _REFLECT_GGX_V_CAVITY_

} // namespace reflect

#endif // _REFLECT_MICROFACET_GGX_INL_HPP_
