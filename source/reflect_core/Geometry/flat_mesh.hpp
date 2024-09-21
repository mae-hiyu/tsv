/*!
  \file flat_mesh.hpp
  \author takemura
  */

#ifndef _REFLECT_FLAT_MESH_HPP_
#define _REFLECT_FLAT_MESH_HPP_

// Standard C++ library
#include <utility>
// Reflect
#include "geometry.hpp"
#include "triangle_mesh.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

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
  No detailed.
  */
class FlatMesh : public TriangleMesh
{
 public:
  //! Create flat mesh
  FlatMesh(const Point3& vertex0, const Point3& vertex1, const Point3& vertex2);


  //! Return the bounding box
  Aabb boundingBox() const override;

  //! Test ray-triangle intersection
  bool isIntersected(const Ray& ray, IntersectionInfo* intersection) const override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample a point randomly on the surface of the triangle
  std::pair<SampledPoint, Vector3> samplePoint(Sampler& sampler) const override;

  //! Sample a point randomly on the surface of the triangle using importance sampling
  std::pair<SampledPoint, Vector3> samplePoint(
      const IntersectionInfo& intersection,
      Sampler& sampler) const override;

  //! Apply affine transformation
  void transform(const Matrix4x4& matrix) override;

 private:
  void initialize(const Point3& vertex1, const Point3& vertex2);

  //! Set normal vector
  void setNormal();


  Point3 vertex_;
  Vector3 edge_[2]; // v0 to v1 and v0 to v2 edge vectors
  Vector3 normal_;
};

//! \} Geometry

} // namespace reflect

#endif // _REFLECT_FLAT_MESH_HPP_
