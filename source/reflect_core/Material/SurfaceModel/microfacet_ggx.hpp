/*!
  \file microfacet_ggx.hpp
  \author takemura
  */

#ifndef _REFLECT_MICROFACET_GGX_HPP_
#define _REFLECT_MICROFACET_GGX_HPP_

// Standard C++ library
#include <cstddef>
#include <utility>
// Reflect
#include "reflect_config.hpp"

namespace reflect {

// Forward declaration
class SampledDirection;
template <std::size_t> class SampledSpectra;
class Sampler;

//! Evaluate GGX D
double evaluateGgxD(const double roughness, const double cos_theta_m);

//! Evaluate GGX G1 term
double evaluateGgxG1(const double roughness, 
                     const double cos_theta_omega, 
                     const double cos_theta_m,
                     const double cos_theta_momega);

//! Evaluate GGX G2 term
double evaluateGgxG2(const double roughness,
                     const double cos_theta_i,
                     const double cos_theta_o,
                     const double cos_theta_m,
                     const double cos_theta_mi,
                     const double cos_theta_mo);

//! Evaluate the GGX reflectance
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> evaluateGgxReflectance(
    const double roughness,
    const Vector3& vin,
    const Vector3& vout,
    const Vector3& normal,
    const SampledSpectra<kSampleSize>& r0,
    const double cos_theta_i,
    const double cos_theta_o);

//! Evaluate the GGX reflectance
double evaluateGgxReflectance(const double roughness,
                              const Vector3& vin,
                              const Vector3& vout,
                              const Vector3& normal,
                              const double n,
                              const double cos_theta_i,
                              const double cos_theta_o);

//! Evaluate the GGX transmittance 
double evaluateGgxTransmittance(const double roughness,
                                const Vector3& vin,
                                const Vector3& vout,
                                const Vector3& normal,
                                const double n,
                                const double cos_theta_i,
                                const double cos_theta_o);

//! Evaluate the GGX weight
double evaluateGgxWeight(const double roughness,
                         const double cos_theta_i,
                         const double cos_theta_o,
                         const double cos_theta_m,
                         const double cos_theta_mi,
                         const double cos_theta_mo);

//! Sample GGX microfacet normal
SampledDirection sampleGgxMicrofacetNormal(const double roughness,
                                           const Vector3& vin,
                                           const Vector3& normal,
                                           Sampler& sampler,
                                           double* cos_i,
                                           double* cos_m,
                                           double* cos_mi);

#define _REFLECT_GGX_V_CAVITY_

} // namespace reflect

#include "microfacet_ggx-inl.hpp"

#endif // _REFLECT_MICROFACET_GGX_HPP_
