/*!
  \file microfacet.hpp
  \author takemura
  */

#ifndef _REFLECT_MICROFACET_HPP_
#define _REFLECT_MICROFACET_HPP_

// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

// Forward declaration
class Sampler;
class SampledDirection;

//! Calculate microfacet reflection direction
SampledDirection getMicrofacetReflectionDirection(
    const Vector3& vin,
    const SampledDirection& microfacet_normal,
    const double cos_theta_mi);

//! Get microfacet reflection half-vector
Vector3 getMicrofacetReflectionHalfVector(const Vector3& vin, 
                                          const Vector3& vout,
                                          const double cos_theta_i);

//! Get microfacet reflection inverse jacobian
double getMicrofacetReflectionInverseJacobian(const double cos_theta_mi);

//! Calculate microfacet refraction direction
SampledDirection getMicrofacetRefractionDirection(
    const Vector3& vin,
    const SampledDirection& microfacet_normal,
    const double cos_theta_mi,
    const double n,
    const double g,
    double* cos_mo);

//! Get microfacet reflection half-vector
Vector3 getMicrofacetRefractionHalfVector(const Vector3& vin, 
                                          const Vector3& vout,
                                          const double n);

//! Get microfacet reflection inverse jacobian
double getMicrofacetRefractionInverseJacobian(const double cos_theta_mi,
                                              const double cos_theta_mo,
                                              const double n);

} // namespace reflect

#include "microfacet-inl.hpp"

#endif // _REFLECT_MICROFACET_HPP_
