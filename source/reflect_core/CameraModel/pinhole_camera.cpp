/*!
 \file pinhole_camera.cpp
 \author takemura
 */

#include "pinhole_camera.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/math.hpp"
#include "zisc/unit.hpp"
// Reflect
#include "camera_model.hpp"
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/transformation.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_direction.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/size.hpp"
#include "Utility/value.hpp"

namespace reflect {

// Forward declaration
class ColorSystem;

/*!
  \details
  No detailed.
  */
PinholeCamera::PinholeCamera(const ColorSystem& color_system,
                             const QSettings& settings, 
                             const QString& prefix) :
    CameraModel(color_system, settings, prefix),
    pinhole_position_{0.0, 0.0, 0.0},
    film_position_{0.0, 0.0, -1.0},
    film_axis1_{-1.0, 0.0, 0.0},
    film_axis2_{0.0, -1.0, 0.0}
{
  initialize(settings, prefix);
}

/*!
  \details
  No detailed.
  */
double PinholeCamera::getDirectionPdf(const double cos_theta) const
{
  const double pdf = 1.0 / (film_area_ * cos_theta * cos_theta * cos_theta);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(pdf);
  return pdf;
}

/*!
  \details
  No detailed.
  */
std::size_t PinholeCamera::printMemberData()
{
  std::size_t size = 0;
  size += CameraModel::printMemberData();
  size += PRINT_VARIABLE_DATA(pinhole_position_);
  size += PRINT_VARIABLE_DATA(film_position_);
  size += PRINT_VARIABLE_DATA(film_axis1_);
  size += PRINT_VARIABLE_DATA(film_axis2_);
  size += PRINT_VARIABLE_DATA(film_area_);
  size += PRINT_VARIABLE_DATA(angle_of_view_);
  return size;
}

/*!
  \details
  No detailed.
  */
SampledDirection PinholeCamera::sampleDirection(const std::size_t x, 
                                                const std::size_t y) const
{
  // Pinhole point
  const auto& pinhole_point = sampledLensPoint();
  // Film point
  const auto coordinate = film().coordinate(x, y, jittering());
  const double p[] = {0.5 - coordinate[0], 0.5 - coordinate[1]};
  const auto film_point = film_position_ + p[0] * film_axis1_ + p[1] * film_axis2_;
  // Ray direction
  const auto direction = (pinhole_point - film_point).normalized();
  // Normal

  const double cos_theta = zisc::dot(normal(), direction);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta);
  const double pdf = 1.0 / (film_area_ * cos_theta * cos_theta * cos_theta);
//  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(pdf);
  return SampledDirection{direction, pdf};
}

/*!
  \details
  No detailed.
  */
void PinholeCamera::sampleLensPoint(Sampler& /* sampler */)
{
  setSampledLensPoint(pinhole_position_);
}

/*!
  \details
  No detailed.
  */
CameraType PinholeCamera::type() const
{
  return CameraType::Pinhole;
}

/*!
  \details
  No detailed.
  */
void PinholeCamera::initialize(const QSettings& settings, const QString& prefix)
{
  const auto key = prefix + "/" + keyword::angle_of_view;
  const double angle = value<double>(settings, key);
  angle_of_view_ = zisc::toRadian(angle);
  setNormal((pinhole_position_ - film_position_).normalized());
}

/*!
  \details
  No detailed.
  */
void PinholeCamera::initializeFilm()
{
  const double theta = angle_of_view_ * 0.5;
  const double r = std::tan(theta);

  const double phi = std::atan(film().inverseAspectRatio());

  const double w = 2.0 * r * std::cos(phi);
  const double h = 2.0 * r * std::sin(phi);

  film_axis1_ = w * film_axis1_.normalized();
  film_axis2_ = h * film_axis2_.normalized();

  film_area_ = w * h;
}

/*!
 \details
 No detailed.
 */
void PinholeCamera::transform(const Matrix4x4& matrix)
{
  affineTransform(matrix, &pinhole_position_);
  affineTransform(matrix, &film_position_);
  affineTransform(matrix, &film_axis1_);
  affineTransform(matrix, &film_axis2_);

  setNormal((pinhole_position_ - film_position_).normalized());
}

} // namespace reflect
