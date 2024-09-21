/*!
  \file lambert_brdf.hpp
  \author takemura
  */

#ifndef _REFLECT_LAMBERT_BRDF_HPP_
#define _REFLECT_LAMBERT_BRDF_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/math.hpp"
// Reflect
#include "reflect_config.hpp"
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
class LambertBrdf : public DiffuseShaderModel<kSampleSize>
{
 public:
  using Spectra = typename ShaderModel<kSampleSize>::Spectra;
  using Wavelengths = typename ShaderModel<kSampleSize>::Wavelengths;


  //! Create a Lambert BRDF
  LambertBrdf(const Vector3& normal, const Spectra& reflectance);


  //! Evaluate the weight of solid angle sampling
  Spectra evaluateWeight(const Vector3* vin,
                         const SampledDirection* vout,
                         const Wavelengths& wavelengths) const override;

  //! Evaluate the BRDF of the area sampling
  Spectra evaluateRadiance(const Vector3* vin,
                           const Vector3* vout,
                           const Wavelengths& wavelengths) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample a reflection direction
  SampledDirection sampleDirection(Sampler& sampler) const override;

  //! Check is wavelength selection occured
  bool wavelengthIsSelected() const override;

 private:
  static constexpr double k = 1.0 / zisc::kPi;

  const Vector3* normal_;
  Spectra reflectance_;
};

//! \} Material

} // namespace reflect

#include "lambert_brdf-inl.hpp"

#endif // _REFLECT_LAMBERT_BRDF_HPP_
