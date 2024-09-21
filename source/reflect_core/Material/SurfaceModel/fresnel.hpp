/*!
  \file fresnel.hpp
  \author takemura
  */

#ifndef _REFLECT_FRESNEL_HPP_
#define _REFLECT_FRESNEL_HPP_

// Standard C++ library
#include <cstddef>
#include <utility>
// Reflect
#include "Color/spectral_distribution.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

// Forward declaration
template <std::size_t> class SampledSpectra;

//! Calculate fresnel 0 degree reflectance for conductor
SpectralDistribution calculateFresnelConductorReflectance0(
    const SpectralDistribution& eta,
    const SpectralDistribution& eta_k);

//! Calculate the fresnel reflection direction
Vector3 getFresnelReflectionDirection(const Vector3& vin,
                                      const Vector3& normal,
                                      const double cos_theta);

//! Calculate the fresnel refraction direction
Vector3 getFresnelRefractionDirection(const Vector3& vin,
                                      const Vector3& normal,
                                      const double cos_theta,
                                      const double n,
                                      const double g);

//! Calculate fresnel dielectric g term
std::pair<bool, double> evaluateFresnelG(const double n, const double cos_theta);

//! Solve fresnel conductor equation
template <std::size_t kSampleSize>
SampledSpectra<kSampleSize> solveFresnelConductorEquation(
    const double cos_theta,
    const SampledSpectra<kSampleSize>& r0);

//! Solve fresnel conductor equation
//SampledSpectra solveFresnelConductorEquation(const double cos_theta,
//                                             const SampledSpectra& eta,
//                                             const SampledSpectra& eta_k);

//! Solve fresnel dielectric equation
double solveFresnelDielectricEquation(const double cos_theta, const double g);

} // namespace reflect

#include "fresnel-inl.hpp"

#endif // _REFLECT_FRESNEL_HPP_
