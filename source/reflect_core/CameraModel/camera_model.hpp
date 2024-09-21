/*!
 \file camera_model.hpp
 \author takemura
 */

#ifndef _REFLECT_CAMERA_MODEL_HPP_
#define _REFLECT_CAMERA_MODEL_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Utility/unique_pointer.hpp"

// Forward decralation
class QSettings;
class QString;

namespace reflect {

// Forward decralation
class ColorSystem;
class Film;
template <std::size_t> class SampledSpectra;
class Sampler;
template <std::size_t> class ShaderModel;
template <std::size_t> class WavelengthSamples;

//! \addtogroup CameraModel
//! \{

/*!
  \details
  No detailed.
  */
enum class CameraType : int
{
  Pinhole = 0,
  ThinLens
};

/*!
 \details
 No detailed.
 */
class CameraModel
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = UniquePointer<ShaderModel<kSampleSize>>;


  //! Create camera
  CameraModel(const ColorSystem& color_system,
              const QSettings& settings, 
              const QString& prefix);

  virtual ~CameraModel() {}


  //! Add ray radiance to film
  template <std::size_t kSampleSize>
  void addContribution(const std::size_t x, 
                       const std::size_t y, 
                       const SampledSpectra<kSampleSize>& contribution);

  //! Return the film
  Film& film();

  //! Return the film
  const Film& film() const;

  //! Get the direction pdf
  virtual double getDirectionPdf(const double cos_theta) const = 0;

  //! Make a sensor
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeSensor(
      const std::size_t x,
      const std::size_t y,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the camera normal
  const Vector3& normal() const;

  //! Return the height resolution of the film
  std::size_t heightResolution() const;

  //! Jitter the point on the pixel
  void jitter(Sampler& sampler);

  //! Return the jittering
  const Vector2& jittering() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the sampled point
  const Point3& sampledLensPoint() const;

  //! Sample lens point
  virtual void sampleLensPoint(Sampler& sampler) = 0;

  //! Sample ray direction
  virtual SampledDirection sampleDirection(const std::size_t x, 
                                           const std::size_t y) const = 0;

  //! Set a film
  void setFilm(Film* film);

  //! Apply affine transformation
  virtual void transform(const Matrix4x4& matrix) = 0;

  //! Return the camera type
  virtual CameraType type() const = 0;

  //! Return the width resolution of the film
  std::size_t widthResolution() const;

 protected:
  //! Set normal
  void setNormal(const Vector3& normal);

  //! Set sampled lens point
  void setSampledLensPoint(const Point3& sampled_point);

 private:
  //! Initialize
  void initialize(const ColorSystem& color_system,
                  const QSettings& settings, 
                  const QString& prefix);

  //! Initialize camera film
  virtual void initializeFilm() = 0;


  Vector3 normal_;
  Point3 sampled_lens_point_;
  Vector2 jittering_;
  Film* film_;
};

//! Make camera
UniquePointer<CameraModel> makeCameraModel(const ColorSystem& color_system,
                                           const QSettings& settings, 
                                           const QString& prefix);

//! \} CameraModel

} // namespace reflect

#include "camera_model-inl.hpp"

#endif // _REFLECT_CAMERA_MODEL_HPP_
