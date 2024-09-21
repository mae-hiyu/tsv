/*!
  \file ggx_dielectric_bsdf.hpp
  \author takemura
  */

#ifndef _REFLECT_GGX_DIELECTRIC_BSDF_HPP_
#define _REFLECT_GGX_DIELECTRIC_BSDF_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

// Forward declaration
class Sampler;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class GgxDielectricBsdf : public GlossyShaderModel<kSampleSize>
{
 public:
  using Spectra = typename ShaderModel<kSampleSize>::Spectra;
  using Wavelengths = typename ShaderModel<kSampleSize>::Wavelengths;


  //! Create a GGX dielectric BSDF
  GgxDielectricBsdf(const double roughness,
                    const Vector3& normal,
                    const double n,
                    const SampledDirection& vout,
                    const double weight);


  //! Evaluate the weight (Fs(i, o, n) * cos(theta_o) / pdf) of solid angle sampling
  Spectra evaluateWeight(const Vector3* vin,
                         const SampledDirection* vout,
                         const Wavelengths& wavelengths) const override;

  //! Evaluate the radiance of the area sampling
  Spectra evaluateRadiance(const Vector3* vin,
                           const Vector3* vout,
                           const Wavelengths& wavelengths) const override;

  //! Print a member variable data
  static std::size_t printMemberData();

  //! Sample a next direction
  SampledDirection sampleDirection(Sampler& sampler) const override;

  //! Check if wavelength selection occured
  bool wavelengthIsSelected() const override;

 private:
  const double n_;
  const double weight_;
  const SampledDirection vout_;
  const double roughness_;
  const Vector3* normal_;
};

//! \} Material

} // namespace reflect

#include "ggx_dielectric_bsdf-inl.hpp"

#endif // _REFLECT_GGX_DIELECTRIC_BSDF_HPP_
