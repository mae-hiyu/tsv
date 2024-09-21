/*!
  \file microfacet_ggx.cpp
  \author takemura
  */

#include "microfacet_ggx.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <utility>
// Zisc
#include "zisc/math.hpp"
// Reflect
#include "fresnel.hpp"
#include "microfacet.hpp"
#include "reflect_config.hpp"
#include "LinearAlgebra/transformation.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/floating_point.hpp"

namespace reflect {

//! Implementation of microfacet normal sampling method
SampledDirection sampleGgxMicrofacetNormal(const double roughness,
                                           const Vector3& vin,
                                           Sampler& sampler,
                                           double* cos_mi);

/*!
  \details
  No detailed.
  */
double evaluateGgxReflectance(const double roughness,
                              const Vector3& vin,
                              const Vector3& vout,
                              const Vector3& normal,
                              const double n,
                              const double cos_theta_i,
                              const double cos_theta_o)
{
  // Calculate reflection half vector
  const auto m_normal = getMicrofacetReflectionHalfVector(vin, vout, cos_theta_i);

  const double cos_theta_m = zisc::dot(normal, m_normal);
  const double cos_theta_mi = -zisc::dot(m_normal, vin);
  const double cos_theta_mo = cos_theta_mi;

  // Evaluate D
  if (cos_theta_i * cos_theta_mi < 0.0)
    return 0.0;
  const double d = evaluateGgxD(roughness, cos_theta_m);

  // Evaluate G2(i, o, m)
  const double g2 = evaluateGgxG2(roughness, cos_theta_i, cos_theta_o,
                                  cos_theta_m, cos_theta_mi, cos_theta_mo);
  if (g2 == 0.0)
    return 0.0;

  // Evaluate the fresnel reflectance
  const auto g = evaluateFresnelG(n, cos_theta_mi);
  const double fresnel = (g.first)
      ? solveFresnelDielectricEquation(cos_theta_mi, g.second)
      : 1.0;
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(fresnel);
  if (fresnel == 0.0)
    return 0.0;

  const double scale_factor = 4.0 * cos_theta_i * cos_theta_o;

  const double f = fresnel * g2 * d / scale_factor;
  REFLECT_CHECK_POSITIVE_FLOAT(f);
  return f;
}

/*!
  \details
  No detailed.
  */
double evaluateGgxTransmittance(const double roughness,
                                const Vector3& vin,
                                const Vector3& vout,
                                const Vector3& normal,
                                const double n,
                                const double cos_theta_i,
                                const double cos_theta_o)
{
  // Calculate refraction half vector
  const auto m_normal = getMicrofacetRefractionHalfVector(vin, vout, n);

  const double cos_theta_m = zisc::dot(normal, m_normal);
  const double cos_theta_mi = -zisc::dot(m_normal, vin);
  const double cos_theta_mo = zisc::dot(m_normal, vout);

  // Evaluate D
  if (cos_theta_i * cos_theta_mi < 0.0)
    return 0.0;
  const double d = evaluateGgxD(roughness, cos_theta_m);

  // Evaluate G2(i, o, m)
  const double g2 = evaluateGgxG2(roughness, cos_theta_i, cos_theta_o,
                                  cos_theta_m, cos_theta_mi, cos_theta_mo);
  if (g2 == 0.0)
    return 0.0;

  // Evaluate the fresnel reflectance
  const auto g = evaluateFresnelG(n, cos_theta_mi);
  if (!g.first)
    return 0.0;
  const double fresnel = 1.0 - solveFresnelDielectricEquation(cos_theta_mi, g.second);
  if (fresnel == 0.0)
    return 0.0;

  const double k1 = cos_theta_mi * cos_theta_mo / (cos_theta_i * cos_theta_o);
  const double tmp = cos_theta_mi + n * cos_theta_mo;
  const double k2 = n * n / (tmp * tmp);

  const double f = fresnel * g2 * d * std::abs(k1) * k2;
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(f);
  return f;
}

/*!
  \details
  No detailed.
  */
SampledDirection sampleGgxMicrofacetNormal(const double roughness,
                                           const Vector3& vin,
                                           const Vector3& normal,
                                           Sampler& sampler,
                                           double* cos_i,
                                           double* cos_m,
                                           double* cos_mi)
{
  // Get change basis matrix
  const double cos_theta_i = -zisc::dot(normal, vin);
  const auto& z_axis = normal;
  const auto x_axis = (vin + cos_theta_i * normal).normalized();
  REFLECT_CHECK_UNIT_VECTOR(x_axis);
  const auto y_axis = zisc::cross(x_axis, z_axis);
  REFLECT_CHECK_UNIT_VECTOR(y_axis);
  const Matrix3x3 transformation{x_axis[0], x_axis[1], x_axis[2], 
                                 y_axis[0], y_axis[1], y_axis[2], 
                                 z_axis[0], z_axis[1], z_axis[2]};

  // Change basis of the incident vector
  const auto in_vector = transformation * -vin;
  REFLECT_CHECK_UNIT_VECTOR(in_vector);

  auto m_normal = sampleGgxMicrofacetNormal(roughness, in_vector, sampler, cos_mi);

  *cos_i = cos_theta_i;
  *cos_m = m_normal.direction()[2];
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(*cos_i);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(*cos_m);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(*cos_mi);

  m_normal.setDirection(transformation.transposedMatrix() * m_normal.direction());
  REFLECT_CHECK_UNIT_VECTOR(m_normal.direction());
  return m_normal;
}

#ifdef _REFLECT_GGX_V_CAVITY_

/*!
  \details
  No detailed.
  */
SampledDirection sampleGgxMicrofacetNormal(const double roughness,
                                           const Vector3& vin,
                                           Sampler& sampler,
                                           double* cos_mi)
{
  const double u1 = sampler.sample(0.0, 1.0);
  const double u2 = sampler.sample(0.0, 1.0);

  // Sample microfacet normal
  const double t = roughness * std::sqrt(u1 / (1.0 - u1));
  const double phi = 2.0 * zisc::kPi * u2;
  const double x = t * std::cos(phi);
  const double y = t * std::sin(phi);
  auto microfacet_normal = Vector3{-x, -y, 1.0}.normalized();
  Vector3 reverse_normal{-microfacet_normal[0],
                         -microfacet_normal[1],
                         microfacet_normal[2]};

  // Swap normal
  double cos_theta_mi = zisc::dot(vin, microfacet_normal);
  const double cos_theta_hi = zisc::dot(vin, reverse_normal);
  const double clamped_cos_mi = zisc::clamp(0.0, 1.0, cos_theta_mi);
  const double clamped_cos_hi = zisc::clamp(0.0, 1.0, cos_theta_hi);
  const double u = sampler.sample(0.0, 1.0);
  if (u < (clamped_cos_hi / (clamped_cos_mi + clamped_cos_hi))) {
    microfacet_normal = reverse_normal;
    cos_theta_mi = cos_theta_hi;
  }
  REFLECT_CHECK_UNIT_VECTOR(microfacet_normal);

  *cos_mi = cos_theta_mi;

  //! \todo Calculate microfacet normal PDF
  constexpr double pdf = 1.0;
  return SampledDirection{microfacet_normal, 1.0 / pdf};
}

#else // _REFLECT_GGX_V_CAVITY_

/*!
  \details
  No detailed.
  */
//std::pair<double, double> sampleGgxSlopeXY(const double cos_theta, Sampler& sampler)
//{
//  const double u1 = sampler.sample(0.0, 1.0);
//  double u2 = sampler.sample(0.0, 1.0);
//
//  // Special case (normal incidence)
//  constexpr double threshold = 0.999999995;
//  if (cos_theta > threshold) {
//    const double r = std::sqrt(u1 / (1.0 - u1));
//    const double phi = 2.0 * zisc::kPi * u2;
//    return std::make_pair(r * std::cos(phi), r * std::sin(phi));
//  }
//
//  // Precomputations
//  const double tan_theta2 = 1.0 / (cos_theta * cos_theta) - 1.0;
//  const double tan_theta = std::sqrt(tan_theta2);
//  const double g1 = 2.0 / (1.0 + std::sqrt(1.0 + tan_theta2));
//  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(g1);
//
//  // Sample slope_x
//  const double a = 2.0 * u1 / g1 - 1.0;
//  const double b = tan_theta;
//  const double tmp = 1.0 / (a * a - 1.0);
//  const double d = std::sqrt((b * b * (tmp + 1.0) - a * a) * tmp);
//  const double slope_x_1 = b * tmp - d;
//  const double slope_x_2 = b * tmp + d;
//  const double slope_x = (a < 0.0 || slope_x_2 > (1.0 / tan_theta))
//      ? slope_x_1
//      : slope_x_2;
//  REFLECT_CHECK_VALID_FLOAT(slope_x);
//
//  // Sample slope_y
//  double s;
//  if (u2 > 0.5) {
//    s = 1.0;
//    u2 = 2.0 * (u2 - 0.5);
//  }
//  else {
//    s = -1.0;
//    u2 = 2.0 * (0.5 - u2);
//  }
//  const double z = (u2 * (u2 * (u2 * 0.27385 - 0.73369) + 0.46341)) / 
//                   (u2 * (u2 * (u2 * 0.093073 + 0.309420) - 1.0) + 0.597999);
//  const double slope_y = s * z * std::sqrt(1.0 + slope_x * slope_x);
//  REFLECT_CHECK_VALID_FLOAT(slope_y);
//
//  return std::make_pair(slope_x, slope_y);
//}
//
///*!
//  \details
//  No detailed.
//  */
//inline
//double evaluateGgxMicrofacetNormalInversePdf(const double roughness,
//                                             const double cos_theta_i,
//                                             const double cos_theta_m,
//                                             const double cos_theta_mi)
//{
//  const double g = evaluateGgxG1(roughness, cos_theta_i, cos_theta_m, cos_theta_mi);
//  const double d = evaluateGgxD(roughness, cos_theta_m);
//  return cos_theta_i / (g * cos_theta_mi * d);
//}
//
///*!
//  \details
//  No detailed.
//  */
//SampledDirection sampleGgxMicrofacetNormal(const double roughness,
//                                           const Vector3& vin,
//                                           const Vector3& normal,
//                                           Sampler& sampler,
//                                           double* cos_i,
//                                           double* cos_m,
//                                           double* cos_mi)
//{
//  // Get basis vector
//  const double cos = -zisc::dot(normal, vin);
//  const double sin = std::sqrt(1.0 - cos * cos);
//  const auto& z_axis = normal;
//  const auto x_axis = (1.0 / sin) * (vin + cos * normal);
//  REFLECT_CHECK_UNIT_VECTOR(x_axis);
//  const auto y_axis = zisc::cross(x_axis, z_axis).normalized();
//
//  // Change basis of the incident vector
//  const Matrix3x3 transformation{x_axis[0], y_axis[0], z_axis[0],
//                                 x_axis[1], y_axis[1], z_axis[1],
//                                 x_axis[2], y_axis[2], z_axis[2]};
//  const auto incident_vector = transformation.inverseMatrix() * -vin;
//  REFLECT_CHECK_UNIT_VECTOR(incident_vector);
//
//  // Stretch microsurface
//  const auto vin_dash = stretchGgxMicrosurface(roughness, incident_vector);
//
//  const double cos_theta = vin_dash[2];
//  double cos_phi = 1.0;
//  double sin_phi = 0.0;
//  if (cos_theta < 0.99999) {
//    const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
//    const double inverse_sin_theta = 1.0 / sin_theta;
//    cos_phi = vin_dash[0] * inverse_sin_theta;
//    sin_phi = vin_dash[1] * inverse_sin_theta;
//  }
//
//  // Sample slope x, y
//  const auto slope = sampleGgxSlopeXY(cos_theta, sampler);
//
//  // Rotate and unstretch
//  const double slope_x = roughness * (cos_phi * slope.first - sin_phi * slope.second);
//  const double slope_y = roughness * (sin_phi * slope.first + cos_phi * slope.second);
//
//  // Compute normal
//  auto microfacet_normal = Vector3{-slope_x, -slope_y, 1.0}.normalized();
//  const double cos_theta_mi = zisc::dot(microfacet_normal, incident_vector);
//
//  // Asign cos_theta
//  *cos_i = incident_vector[2];
//  *cos_m = microfacet_normal[2];
//  *cos_mi = cos_theta_mi;
//
//  // Calculate PDF
//  const double inverse_pdf = 
//      evaluateGgxMicrofacetNormalInversePdf(roughness, 
//                                            incident_vector[2], 
//                                            microfacet_normal[2],
//                                            cos_theta_mi);
//  microfacet_normal = transformation * microfacet_normal;
//  REFLECT_CHECK_UNIT_VECTOR(microfacet_normal);
//
//  return SampledDirection{microfacet_normal, inverse_pdf};
//}

#endif // _REFLECT_GGX_V_CAVITY_

} // namespace reflect
