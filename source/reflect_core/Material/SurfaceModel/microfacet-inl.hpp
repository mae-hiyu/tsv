/*!
  \file microfacet-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_MICROFACET_INL_HPP_
#define _REFLECT_MICROFACET_INL_HPP_

#include "microfacet.hpp"
// Standard C++ library
#include <cmath>
// Zisc
#include "zisc/math.hpp"
// Standard C++ library
#include <cmath>
#include <utility>
// Reflect
#include "fresnel.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Utility/floating_point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
SampledDirection getMicrofacetReflectionDirection(
    const Vector3& vin,
    const SampledDirection& microfacet_normal,
    const double cos_theta_mi)
{
  const auto& normal = microfacet_normal.direction();
  const auto vout = getFresnelReflectionDirection(vin, normal, cos_theta_mi);
  const double jacobian = getMicrofacetReflectionInverseJacobian(cos_theta_mi);
  const double inverse_pdf = jacobian * microfacet_normal.inversePdf();
  return SampledDirection{vout, inverse_pdf};
}

/*!
  \details
  No detailed.
  */
inline
Vector3 getMicrofacetReflectionHalfVector(const Vector3& vin, 
                                          const Vector3& vout,
                                          const double cos_theta_i)
{
  const auto half_vector = (cos_theta_i > 0.0) ? vout - vin : vin - vout;
  return half_vector.normalized();
}

/*!
  \details
  No detailed.
  */
inline
double getMicrofacetReflectionInverseJacobian(const double cos_theta_mi)
{
  const double jacobian = 4.0 * cos_theta_mi;
  REFLECT_CHECK_POSITIVE_FLOAT(jacobian);
  return jacobian;
}

/*!
  \details
  No detailed.
  */
inline
SampledDirection getMicrofacetRefractionDirection(
    const Vector3& vin,
    const SampledDirection& microfacet_normal,
    const double cos_theta_mi,
    const double n,
    const double g,
    double* cos_mo)
{
  // Direction
  const auto& normal = microfacet_normal.direction();
  const auto vout = getFresnelRefractionDirection(vin, normal, cos_theta_mi, n, g);
  // Jacobian
  const double cos_theta_mo = zisc::dot(normal, vout);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(-cos_theta_mo);
  const double jacobian = getMicrofacetRefractionInverseJacobian(cos_theta_mi,
                                                                 cos_theta_mo,
                                                                 n);
  const double inverse_pdf = jacobian * microfacet_normal.inversePdf();

  *cos_mo = cos_theta_mo;
  return SampledDirection{vout, inverse_pdf};
}

/*!
  \details
  No detailed.
  */
inline
Vector3 getMicrofacetRefractionHalfVector(const Vector3& vin,
                                          const Vector3& vout,
                                          const double n)
{
  return (vin - n * vout).normalized();
}

/*!
  \details
  No detailed.
  */
inline
double getMicrofacetRefractionInverseJacobian(const double cos_theta_mi,
                                              const double cos_theta_mo,
                                              const double n)
{
  const double t = cos_theta_mi + n * cos_theta_mo;
  const double jacobian = (t * t) / (n * n * std::abs(cos_theta_mo));
  REFLECT_CHECK_POSITIVE_FLOAT(jacobian);
  return jacobian;
}

} // namespace reflect

#endif // _REFLECT_MICROFACET_INL_HPP_
