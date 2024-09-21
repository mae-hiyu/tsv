/*!
  \file sensor.hpp
  \author takemura
  */

#ifndef _REFLECT_SENSOR_HPP_
#define _REFLECT_SENSOR_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Material/shader_model.hpp"
#include "Sampling/sampled_direction.hpp"

namespace reflect {

// Forward declaration
class CameraModel;
template <std::size_t> class SampledSpectra;
class Sampler;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class Sensor : public GlossyShaderModel<kSampleSize>
{
 public:
  using Spectra = typename ShaderModel<kSampleSize>::Spectra;
  using Wavelengths = typename ShaderModel<kSampleSize>::Wavelengths;

   
  //! Create a Camera sensor
  Sensor(const CameraModel* camera,
         const std::size_t x, 
         const std::size_t y, 
         Sampler& sampler);


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
  //! Initialize sensor
  void initialize(const std::size_t x, const std::size_t y, Sampler& sampler);


  const CameraModel* camera_;
  SampledDirection direction_;
};

//! \} Material

} // namespace reflect

#include "sensor-inl.hpp"

#endif // _REFLECT_SENSOR_HPP_
