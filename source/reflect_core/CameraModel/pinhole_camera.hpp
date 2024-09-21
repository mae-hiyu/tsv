/*!
 \file pinhole_camera.hpp
 \author takemura
 */

#ifndef _REFLECT_PINHOLE_CAMERA_HPP_
#define _REFLECT_PINHOLE_CAMERA_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "camera_model.hpp"
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

using zisc::cast;

// Forward declaration
class ColorSystem;
class SampledDirection;
class Sampler;

//! \addtogroup CameraModel
//! \{

/*!
 \details
 No detailed.
 */
class PinholeCamera : public CameraModel
{
 public:
  //! Create a pinhole camera
  PinholeCamera(const ColorSystem& color_system,
                const QSettings& settings, 
                const QString& prefix);


  //! Get the direction pdf
  double getDirectionPdf(const double cos_theta) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample ray direction
  SampledDirection sampleDirection(const std::size_t x, 
                                   const std::size_t y) const override;

  //! Sample pinhole point
  void sampleLensPoint(Sampler& sampler) override;

  //! Apply affine transformation
  void transform(const Matrix4x4& matrix) override;

  //! Return the pinhole camera type
  CameraType type() const override;

 private:
  //! Initialize
  void initialize(const QSettings& settings, const QString& prefix);

  //! Initialize camera film
  void initializeFilm() override;


  Point3 pinhole_position_; //!< The position of pinhole
  Point3 film_position_; //!< Center point of film
  Vector3 film_axis1_,
          film_axis2_;
  double film_area_;
  double angle_of_view_;
};

//! \} CameraModel

} // namespace reflect

#endif // _REFLECT_PINHOLE_CAMERA_HPP_
