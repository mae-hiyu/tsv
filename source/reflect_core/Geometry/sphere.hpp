/*!
  \file sphere.hpp
  \author takemura
  */

#ifndef _REFLECT_SPHERE_HPP_
#define _REFLECT_SPHERE_HPP_

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
class IntersectionInfo;
class Ray;
class Sampler;

//! \addtogroup Geometry 
//! \{

/*!
  \brief Sphere
  \details
  No detailed.
  */
class Sphere : public Geometry
{
 public:
  //! Initialize
  Sphere();


  //! Get bounding box
  Aabb boundingBox() const override;

  //! Test ray-sphere intersection
  bool isIntersected(const Ray& ray, IntersectionInfo* intersection) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample a point randomly on the surface of the sphere
  std::pair<SampledPoint, Vector3> samplePoint(Sampler& sampler) const override;

  //! Sample a point randomly on the surface of the sphere using importance sampling
  std::pair<SampledPoint, Vector3> samplePoint(
      const IntersectionInfo& intersection,
      Sampler& sampler) const override;

  //! Apply affine transformation
  void transform(const Matrix4x4& matrix) override;

 private:
  //! Return texture coordinate
  Point2 calculateTextureCoordinate(const Vector3& normal) const;

  //! Initialize
  void initialize();

  //! Set radius of a sphere
  void setRadius(const double radius);

  //! Test ray-sphere intersection
  bool testIntersection(const Ray& ray, Point3* point) const;


  Point3 center_;
  Vector3 axis1_,
          axis2_,
          axis3_;
  double radius_,
         square_radius_,
         inverse_radius_;
};

//! \} Geometry

} // namespace reflect

#endif // _REFLECT_SPHERE_HPP_
