/*!
 \file plane.cpp
 \author takemura
 */

#include "plane.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
// Zisc
#include "zisc/arithmetic_array.hpp"
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
Plane::Plane() :
    top_left_{-0.5, 0.0, -0.5},
    normal_{0.0, 1.0, 0.0},
    axis1_{1.0, 0.0, 0.0},
    axis2_{0.0, 0.0, 1.0},
    square_width_{1.0},
    square_height_{1.0}
{
  initialize();
}

/*!
 \details
 No detailed.
 */
Aabb Plane::boundingBox() const
{
  auto min_point = top_left_.data();
  auto max_point = top_left_.data();
  Point3 plane_points[] = {top_left_ + axis1_, 
                           top_left_ + axis2_, 
                           top_left_ + axis1_ + axis2_};
  for (const auto& point : plane_points) {
    min_point = zisc::minElements(min_point, point.data());
    max_point = zisc::maxElements(max_point, point.data());
  }
  return Aabb{Point3{min_point}, Point3{max_point}};
}

/*!
 \details
  Please see the details of this algorithm below RUL.
 http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-plane-and-ray-disk-intersection/
 */
bool Plane::isIntersected(const Ray& ray, IntersectionInfo* intersection) const
{
  // Rayが平面と交差するまでの時間tを求めます
  const double cos_theta = dot(normal_, ray.direction());
  // 平面の法線とレイの方向が垂直な関係にある場合は当たらない
  if (cos_theta == 0.0)
    return false;
  const double t = dot(top_left_ - ray.origin(), normal_) / cos_theta;
  if (t < 0.0)
    return false;

  //  交点が矩形の内側にあるか確認します
  const auto point = ray.origin() + (t * ray.direction());
  const auto am = point - top_left_;
  const double dot_axis1_am = zisc::dot(am, axis1_);
  const double dot_axis2_am = zisc::dot(am, axis2_);
  if ((0.0 <= dot_axis1_am) && (dot_axis1_am <= square_width_) &&
      (0.0 <= dot_axis2_am) && (dot_axis2_am <= square_height_)) {
    intersection->setReverseFace(cos_theta > 0.0);
    intersection->setPoint(point);
    intersection->setNormal(normal_);
    const double u = dot_axis1_am * inverse_square_width_;
    const double v = dot_axis2_am * inverse_square_height_;
    REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(u);
    REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(v);
    intersection->setTextureCoordinate(Point2{u, v});
    return true;
  }
  return false;
}

/*!
  \details
  No detailed.
  */
std::size_t Plane::printMemberData()
{
  std::size_t size = 0;
  size += Geometry::printMemberData();
  size += PRINT_VARIABLE_DATA(top_left_);
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(axis1_);
  size += PRINT_VARIABLE_DATA(axis2_);
  size += PRINT_VARIABLE_DATA(square_width_);
  size += PRINT_VARIABLE_DATA(square_height_);
  size += PRINT_VARIABLE_DATA(inverse_square_width_);
  size += PRINT_VARIABLE_DATA(inverse_square_height_);
  return size;
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> Plane::samplePoint(Sampler& sampler) const
{
  const auto point = top_left_ + axis1_ * sampler.sample(0.0, 1.0) +
                                 axis2_ * sampler.sample(0.0, 1.0);
  return std::make_pair(SampledPoint{point, surfaceArea()}, normal_);
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> Plane::samplePoint(
    const IntersectionInfo& /* intersection */,
    Sampler& sampler) const
{
  return samplePoint(sampler);
}

/*!
 \details
 No detailed.
 */
void Plane::transform(const Matrix4x4& matrix)
{
  affineTransform(matrix, &top_left_);
  affineTransform(matrix, &axis1_);
  affineTransform(matrix, &axis2_);

  square_width_ = axis1_.squareNorm();
  square_height_ = axis2_.squareNorm();
  inverse_square_width_ = 1.0 / square_width_;
  inverse_square_height_ = 1.0 / square_height_;
  normal_ = cross(axis2_, axis1_).normalized();
  REFLECT_CHECK_UNIT_VECTOR(normal_);

  const auto area = zisc::cross(axis1_, axis2_).norm();
  setSurfaceArea(area);
}

/*!
  \details
  No detailed.
  */
void Plane::initialize()
{
  setSurfaceArea(axis1_.norm() * axis2_.norm());
}

} // namespace reflect
