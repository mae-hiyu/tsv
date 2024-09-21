/*!
  \file non_directional_light.hpp
  \author takemura
  */

#ifndef _REFLECT_NON_DIRECTIONAL_LIGHT_HPP_
#define _REFLECT_NON_DIRECTIONAL_LIGHT_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/math.hpp"
// Reflect
#include "reflect_config.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_spectra.hpp"

namespace reflect {

// Forward declaration
class SampledDirection;
class Sampler;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class NonDirectionalLight : public DiffuseShaderModel<kSampleSize>
{
 public:
  using Spectra = typename ShaderModel<kSampleSize>::Spectra;
  using Wavelengths = typename ShaderModel<kSampleSize>::Wavelengths;

  //! Create a non-directional light 
  NonDirectionalLight(const Vector3& normal, const Spectra& radiant_emittance);
  

  //! Evaluate the weight of solid angle sampling
  Spectra evaluateWeight(const Vector3* vin,
                         const SampledDirection* vout,
                         const Wavelengths& wavelengths) const override;

  //! Evaluate the radiance of area sampling
  Spectra evaluateRadiance(const Vector3* vin,
                           const Vector3* vout,
                           const Wavelengths& wavelengths) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! This method is not used
  SampledDirection sampleDirection(Sampler& sampler) const override;

  //! Check is wavelength selection occured
  bool wavelengthIsSelected() const override;

 private:
  static constexpr double k = 1.0 / zisc::kPi;


  const Vector3* normal_;
  const Spectra radiant_emittance_;
};

//! \} Material

} // namespace reflect

#include "non_directional_light-inl.hpp"

#endif // _REFLECT_NON_DIRECTIONAL_LIGHT_HPP_
