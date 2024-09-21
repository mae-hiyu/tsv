/*!
 \file plane.hpp
 \author takemura
 */

#ifndef _REFLECT_PLANE_HPP_
#define _REFLECT_PLANE_HPP_

// Standard C++ library
#include <cstddef>
#include <utility>
// Reflect
#include "geometry.hpp"
#include "reflect_config.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_point.hpp"

namespace reflect {

// Forward declaration
class Aabb;
class IntersectionInfo;
class Ray;
class Sampler;

//! \addtogroup Geometry
//! \{

/*!
 \brief 3D plane
 \details
 No detailed.
 */
class Plane : public Geometry 
{
 public:
  //! Initialize
  Plane();

  //! Get bounding box
  Aabb boundingBox() const override;

  //! Test ray-plane intersection
  bool isIntersected(const Ray& ray, IntersectionInfo* intersection) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample a point randomly on the surface of the plane 
  std::pair<SampledPoint, Vector3> samplePoint(Sampler& sampler) const override;

  //! Sample a point randomly on the surface of the plane using importance sampling
  std::pair<SampledPoint, Vector3> samplePoint(const IntersectionInfo& intersection,
                                               Sampler& sampler) const override;

  //! Apply affine transformation
  void transform(const Matrix4x4& matrix) override;
 
 private:
  //! Initialize
  void initialize();


  Point3 top_left_;
  Vector3 normal_;
  Vector3 axis1_,
          axis2_;
  double square_width_,
         square_height_;
  double inverse_square_width_,
         inverse_square_height_;
};

//! \} Geometry

} // namespace reflect

#endif // _REFLECT_PLANE_HPP_
