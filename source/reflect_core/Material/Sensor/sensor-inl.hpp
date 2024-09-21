/*!
  \file sensor-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SENSOR_INL_HPP_
#define _REFLECT_SENSOR_INL_HPP_

#include "sensor.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
#include <iostream>

// Reflect
#include "reflect_config.hpp"
#include "CameraModel/camera_model.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_point.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Utility/size.hpp"


namespace reflect {

// Forward declaration
class Sampler;
template <std::size_t> class WavelengthSamples;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
Sensor<kSampleSize>::Sensor(const CameraModel* camera,
                            const std::size_t x,
                            const std::size_t y,
                            Sampler& sampler) :
    camera_{camera}
{
  initialize(x, y, sampler);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto Sensor<kSampleSize>::evaluateWeight(
    const Vector3* /* vin */,
    const SampledDirection* /* vout */,
    const Wavelengths& wavelengths) const -> Spectra
{
  return Spectra{wavelengths, 1.0};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
auto Sensor<kSampleSize>::evaluateRadiance(
    const Vector3* /* vin */,
    const Vector3* vout,
    const Wavelengths& wavelengths) const -> Spectra
{
  const double cos_theta = zisc::dot(camera_->normal(), *vout);
  const double pdf = camera_->getDirectionPdf(cos_theta);
  const double weight = pdf / cos_theta;
  return Spectra{wavelengths, weight};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
std::size_t Sensor<kSampleSize>::printMemberData()
{
  std::size_t size = 0;
  size += ShaderModel<kSampleSize>::printMemberData();
  size += PRINT_VARIABLE_DATA(camera_);
  size += PRINT_VARIABLE_DATA(direction_);
  return size;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
SampledDirection Sensor<kSampleSize>::sampleDirection(Sampler& /* sampler */) const
{
  return direction_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
bool Sensor<kSampleSize>::wavelengthIsSelected() const
{
  return false;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void Sensor<kSampleSize>::initialize(const std::size_t x,
                                     const std::size_t y,
                                     Sampler& /* sampler */)
{
  const auto sampled_direction = camera_->sampleDirection(x, y);
  direction_ = sampled_direction;
}

} // namespace reflect

#endif // _REFLECT_SENSOR_INL_HPP_
