/*!
  \file specular_bsdf.hpp
  \author takemura
  */

#ifndef _REFLECT_SPECULAR_BSDF_HPP_
#define _REFLECT_SPECULAR_BSDF_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"

namespace reflect {

// Forward declaration
class Sampler;
template <std::size_t> class SampledSpectra;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class SpecularBsdf : public SpecularShaderModel<kSampleSize>
{
 public:
  using Spectra = typename ShaderModel<kSampleSize>::Spectra;
  using Wavelengths = typename ShaderModel<kSampleSize>::Wavelengths;


  //! Create a specular BSDF
  SpecularBsdf(const Vector3& normal,
               const Vector3& vout,
               const double cos_theta_o,
               const double reflectance,
               const double transmittance);


  //! Evalute the weight of solid angle sampling
  Spectra evaluateWeight(const Vector3* vin,
                         const SampledDirection* vout,
                         const Wavelengths& wavelengths) const override;

  //! Evaluate BRDF of area sampling
  Spectra evaluateRadiance(const Vector3* vin,
                           const Vector3* vout,
                           const Wavelengths& wavelengths) const override;

  //! Print member function data
  static std::size_t printMemberData();

  //! Sample a reflection direction
  SampledDirection sampleDirection(Sampler& sampler) const override;

  //! Check if wavelength selection occured
  bool wavelengthIsSelected() const override;

 private:
  const Vector3* normal_;
  const Vector3 vout_;
  const double inverse_cos_theta_o_;
  const double reflectance_;
  const double transmittance_;
};

//! \} Material

} // namespace reflect

#include "specular_bsdf-inl.hpp"

#endif // _REFLECT_SPECULAR_BSDF_HPP_
