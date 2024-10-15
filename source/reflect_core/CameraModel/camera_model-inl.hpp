/*!
 \file camera_model-inl.hpp
 \author takemura
 */

#ifndef _REFLECT_CAMERA_MODEL_INL_HPP_
#define _REFLECT_CAMERA_MODEL_INL_HPP_

#include "camera_model.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
// Reflect
#include "film.hpp"
#include "reflect_config.hpp"
#include "Color/rgb_spectra_image.hpp"
#include "Color/spectral_distribution.hpp"
#include "Color/spectra_image.hpp"
#include "Color/spectra_image_interface.hpp"
#include "Material/Sensor/sensor.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampled_point.hpp"
#include "Sampling/sampler.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void CameraModel::addContribution(const std::size_t x, 
                                  const std::size_t y, 
                                  const SampledSpectra<kSampleSize>& contribution)
{
  auto& spectra_buffer = film_->spectraBuffer();
  spectra_buffer.addContribution(x, y, contribution);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void CameraModel::addXYZSpectraContribution(const std::size_t x, 
                                  const std::size_t y, 
                                  const SampledSpectra<kSampleSize>& contribution)
{
  auto& spectra_buffer = film_->spectraBuffer();
  spectra_buffer.addContribution(x, y, contribution);
}

/*!
  \details
  No detailed.
  */
inline
Film& CameraModel::film()
{
  return *film_;
}

/*!
  \details
  No detailed.
  */
inline
const Film& CameraModel::film() const
{
  return *film_;
}

//! Make a sensor
template <std::size_t kSampleSize>
auto CameraModel::makeSensor(
    const std::size_t x,
    const std::size_t y,
    const WavelengthSamples<kSampleSize>& /* wavelengths */,
    Sampler& sampler,
    MemoryPool& memory_pool) const -> ShaderPointer<kSampleSize>
{
  auto sensor = memory_pool.allocate<Sensor<kSampleSize>>(this, x, y, sampler);
  return ShaderPointer<kSampleSize>{sensor};
}

/*!
  \details
  No detailed.
  */
inline
const Vector3& CameraModel::normal() const
{
  return normal_;
}

/*!
  \details
  No detailed.
  */
inline
std::size_t CameraModel::heightResolution() const
{
  return film_->heightResolution();
}

/*!
  \details
  No detailed.
  */
inline
void CameraModel::jitter(Sampler& sampler)
{
  if (film_->isEnabledJittering()) {
    jittering_[0] = sampler.sample(0.0, 1.0);
    jittering_[1] = sampler.sample(0.0, 1.0);
  }
}

/*!
  \details
  No detailed.
  */
inline
const Vector2& CameraModel::jittering() const
{
  return jittering_;
}

/*!
  \details
  No detailed.
  */
inline
const Point3& CameraModel::sampledLensPoint() const
{
  return sampled_lens_point_;
}

/*!
  \details
  No detailed.
  */
inline
void CameraModel::setFilm(Film* film)
{
  film_ = film;
  initializeFilm();
}

/*!
  \details
  No detailed.
  */
inline
std::size_t CameraModel::widthResolution() const
{
  return film_->widthResolution();
}

/*!
  \details
  No detailed.
  */
inline
void CameraModel::setNormal(const Vector3& normal)
{
  normal_ = normal;
}

/*!
  \details
  No detailed.
  */
inline
void CameraModel::setSampledLensPoint(const Point3& sampled_point)
{
  sampled_lens_point_ = sampled_point;
}

} // namespace reflect

#endif // _REFLECT_CAMERA_MODEL_INL_HPP_
