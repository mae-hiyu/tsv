/*!
  \file smoothed_mesh.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTHED_MESH_HPP_
#define _REFLECT_SMOOTHED_MESH_HPP_

// Standard C++ library
#include <utility>
// Reflect
#include "geometry.hpp"
#include "triangle_mesh.hpp"
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
  \details
  Please see the detail of this algorithm the pdf
  Entitled "Ray tracing simulation method using piecewise quadratic interpolant
  for aspheric optical systems"
  */
class SmoothedMesh : public TriangleMesh 
{
 public:
  //! Initialize smoothed mesh
  SmoothedMesh(const Point3& vertex0, 
               const Point3& vertex1, 
               const Point3& vertex2,
               const Vector3& normal0, 
               const Vector3& normal1,
               const Vector3& normal2);


  //! Return the bounding box
  Aabb boundingBox() const override;

  //! Test ray-mesh intersection
  bool isIntersected(const Ray& ray, IntersectionInfo* intersection) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample a point randomly on the surface of the mesh
  std::pair<SampledPoint, Vector3> samplePoint(Sampler& sampler) const override;

  //! Sample a point randomly on the surface of the mesh using importance sampling
  std::pair<SampledPoint, Vector3> samplePoint(
      const IntersectionInfo& intersection,
      Sampler& sampler) const override;

  //! Apply affine transformation
  void transform(const Matrix4x4& matrix) override;

 private:
  // Calculate the bounding box
  Aabb calculateBoundingBox(const Vector3* distance, const Vector3* curvature) const;

  //! Initialize
  void initialize(const Point3& vertex0,
                  const Point3& vertex1,
                  const Point3& vertex2,
                  const Vector3& normal0,
                  const Vector3& normal1,
                  const Vector3& normal2);

  //! Return the normal
  Vector3 normal(const double eta, const double xi) const;

  //! Return the surface point
  Point3 point(const double eta, const double xi) const;


  Vector3 c_[6]; //!< Vector coefficients of the patch
};

//! \} Geometry

} // namespace reflect

#include "smoothed_mesh-inl.hpp"

#endif // _REFLECT_SMOOTHED_MESH_HPP_
