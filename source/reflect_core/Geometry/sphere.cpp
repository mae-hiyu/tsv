/*!
  \file sphere.cpp
  \author takemura
  */

#include "sphere.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
// Zisc
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "geometry.hpp"
#include "reflect_config.hpp"
#include "Data/intersection_info.hpp"
#include "Data/ray.hpp"
#include "DataStructure/aabb.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "LinearAlgebra/transformation.hpp"
#include "Sampling/sampled_point.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/size.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
Sphere::Sphere() :
    center_{0.0, 0.0, 0.0},
    axis1_{0.0, -1.0, 0.0},
    axis2_{-1.0, 0.0, 0.0},
    axis3_{0.0, 0.0, 1.0},
    radius_{0.5}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
Aabb Sphere::boundingBox() const
{
  return Aabb{center_ - radius_ * Vector3{1.0, 1.0, 1.0},
              center_ + radius_ * Vector3{1.0, 1.0, 1.0}};
}

/*!
  \details
  No detailed.
  */
bool Sphere::isIntersected(const Ray& ray, IntersectionInfo* intersection) const
{
  Point3 point;
  if (!testIntersection(ray, &point))
    return false;

  intersection->setReverseFace(false);
  intersection->setPoint(point);
  const auto normal = (point - center_) * inverse_radius_;
  REFLECT_CHECK_UNIT_VECTOR(normal);
  intersection->setNormal(normal);

  const auto uv_coordinate = calculateTextureCoordinate(intersection->normal());
  intersection->setTextureCoordinate(uv_coordinate);
  return true;
}

/*!
  \details
  No detailed.
  */
std::size_t Sphere::printMemberData()
{
  std::size_t size = 0;
  size += Geometry::printMemberData();
  size += PRINT_VARIABLE_DATA(center_);
  size += PRINT_VARIABLE_DATA(axis1_);
  size += PRINT_VARIABLE_DATA(axis2_);
  size += PRINT_VARIABLE_DATA(axis3_);
  size += PRINT_VARIABLE_DATA(radius_);
  size += PRINT_VARIABLE_DATA(square_radius_);
  size += PRINT_VARIABLE_DATA(inverse_radius_);
  return size;
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> Sphere::samplePoint(Sampler& sampler) const
{
  const double phi = zisc::kPi * sampler.sample(-1.0, 1.0);
  const double cos_theta = 1.0 - sampler.sample(0.0, 2.0);
  const double sin_theta = zisc::sqrt(1.0 - cos_theta * cos_theta);

  const Vector3 normal{sin_theta * zisc::cos(phi),
                       sin_theta * zisc::sin(phi),
                       cos_theta};
  REFLECT_CHECK_UNIT_VECTOR(normal);

  const Point3 sampled_point = center_ + normal * radius_;
  return std::make_pair(SampledPoint{sampled_point, surfaceArea()}, normal);
}

/*!
  \details
  Please see the details of this algorithm below PDF.
  "Monte Carlo Ray Tracing.pdf"
  */
std::pair<SampledPoint, Vector3> Sphere::samplePoint(
    const IntersectionInfo& intersection,
    Sampler& sampler) const
{
  const double phi = zisc::kPi * sampler.sample(-1.0, 1.0);
  const auto center_line = center_ - intersection.point();
  constexpr double k = 0.999;
  const double sin_alpha_max = radius_ * center_line.inverseNorm() * k;
  const double cos_alpha_max = zisc::sqrt(1.0 - sin_alpha_max * sin_alpha_max);
  const double cos_alpha = 1.0 - (1.0 - cos_alpha_max) * sampler.sample(0.0, 1.0);
  const double sin_alpha = zisc::sqrt(1.0 - cos_alpha * cos_alpha);

  Vector3 direction{sin_alpha * zisc::cos(phi),
                    sin_alpha * zisc::sin(phi),
                    cos_alpha};
  REFLECT_CHECK_UNIT_VECTOR(direction);
  changeBasis(center_line.normalized(), &direction);

  const Ray ray{intersection.point(), direction};
  Point3 point;
  if (!testIntersection(ray, &point))
    zisc::raiseError("SphereError: Ray intersection test failed.");

  const auto normal = (point - center_) * inverse_radius_;
  REFLECT_CHECK_UNIT_VECTOR(normal);

  const double cos_theta = -zisc::dot(direction, normal);
  REFLECT_CHECK_NON_ZERO_FLOAT(cos_theta);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(cos_theta);

  const double distance = (point - intersection.point()).squareNorm();
  const double inverse_pdf = distance * 2.0 * zisc::kPi * 
                            (1.0 - cos_alpha_max) / cos_theta;

  return std::make_pair(SampledPoint{point, inverse_pdf}, normal);
}

/*!
  \details
  No detailed.
  */
void Sphere::transform(const Matrix4x4& matrix)
{
  affineTransform(matrix, &center_);

  Vector3 radius{0.0, radius_, 0.0};
  affineTransform(matrix, &radius);
  setRadius(radius.norm());

  affineTransform(matrix, &axis1_);
  affineTransform(matrix, &axis2_);
  affineTransform(matrix, &axis3_);
  axis1_ = 0.5 * inverse_radius_ * axis1_;
  axis2_ = 0.5 * inverse_radius_ * axis2_;
  axis3_ = 0.5 * inverse_radius_ * axis3_;
  REFLECT_CHECK_UNIT_VECTOR(axis1_);
  REFLECT_CHECK_UNIT_VECTOR(axis2_);
  REFLECT_CHECK_UNIT_VECTOR(axis3_);
}

/*!
  \details
  No detailed.
  */
Point2 Sphere::calculateTextureCoordinate(const Vector3& normal) const
{
  const double cos_theta = zisc::dot(axis1_, normal);
  const auto normal_dash = (normal - cos_theta * axis1_).normalized();
  const double cos_phi = zisc::dot(axis2_, normal_dash);

  const double theta = zisc::arcCos(cos_theta);
  const double u = theta * (1.0 / zisc::kPi);
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(u);

  const double phi = (0.0 < zisc::dot(axis3_, normal_dash))
      ? (0.5 * zisc::kPi) + zisc::arcCos(cos_phi)
      : (1.5 * zisc::kPi) - zisc::arcCos(cos_phi);
  const double v = phi * (1.0 / (2.0 * zisc::kPi));
  REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(v);

  return Point2{u, v};
}

/*!
  \details
  No detailed.
  */
void Sphere::initialize()
{
  setRadius(radius_);
}

/*!
  \details
  No detailed.
  */
void Sphere::setRadius(const double radius)
{
  radius_ = radius;
  square_radius_ = radius * radius;
  inverse_radius_ = 1.0 / radius;
  setSurfaceArea(4.0 * zisc::kPi * radius * radius);
}

/*!
  \details
  No detailed.
  */
inline
bool Sphere::testIntersection(const Ray& ray, Point3* point) const
{
  const auto co = ray.origin() - center_;
  const double b = zisc::dot(ray.direction(), co);
  const double c = co.squareNorm() - square_radius_;
  const double discriminant = b * b - c; // discriminant
  if (discriminant < 0.0)
    return false;
  const double t = -(b + zisc::sqrt(discriminant)); // time
  *point = ray.origin() + t * ray.direction();
  return true;
}

} // namespace reflect
