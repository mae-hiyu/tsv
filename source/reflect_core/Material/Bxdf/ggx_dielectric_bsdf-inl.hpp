/*!
  \file ggx_dielectric_bsdf-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_GGX_DIELECTRIC_BSDF_INL_HPP_
#define _REFLECT_GGX_DIELECTRIC_BSDF_INL_HPP_

#include "ggx_dielectric_bsdf.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
GgxDielectricBsdf<kSampleSize>::GgxDielectricBsdf(const double roughness,
                                                  const Vector3& normal,
                                                  const double n,
                                                  const SampledDirection& vout,
                                                  const double weight) :
    n_{n},
    weight_{weight},
    vout_{vout},
    roughness_{roughness},
    normal_{&normal}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto GgxDielectricBsdf<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& wavelengths) const -> Spectra
{
  Spectra reflectance{wavelengths};
  reflectance.setIntensity(wavelengths.primaryWavelengthIndex(), weight_);
  return reflectance;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto GgxDielectricBsdf<kSampleSize>::evaluateRadiance(
    const Vector3* vin,
    const Vector3* vout,
    const Wavelengths& wavelengths) const -> Spectra
{
  const double cos_theta_i = -zisc::dot(*normal_, *vin);
  const double cos_theta_o = zisc::dot(*normal_, *vout);
  const double f = evaluateGgxReflectance(roughness_, *vin, *vout, *normal_, 
                                          n_, cos_theta_i, cos_theta_o) +
                   evaluateGgxTransmittance(roughness_, *vin, *vout, *normal_,
                                          n_, cos_theta_i, cos_theta_o);
  REFLECT_CHECK_POSITIVE_FLOAT(f);

  Spectra reflectance{wavelengths};
  reflectance.setIntensity(wavelengths.primaryWavelengthIndex(), f);
  return reflectance;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t GgxDielectricBsdf<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(n_);
  size += PRINT_VARIABLE_DATA(weight_);
  size += PRINT_VARIABLE_DATA(vout_);
  size += PRINT_VARIABLE_DATA(roughness_);
  size += PRINT_VARIABLE_DATA(normal_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
SampledDirection GgxDielectricBsdf<kSampleSize>::sampleDirection(
    Sampler& /* sampler */) const
{
  return vout_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
bool GgxDielectricBsdf<kSampleSize>::wavelengthIsSelected() const
{
  return true;
}

} // namespace reflect

#endif // _REFLECT_GGX_DIELECTRIC_BSDF_INL_HPP_
