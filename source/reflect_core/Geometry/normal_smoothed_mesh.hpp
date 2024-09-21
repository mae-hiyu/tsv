/*!
  \file normal_smoothed_mesh.hpp
  \author takemura
  */

#ifndef _REFLECT_NORMAL_SMOOTHED_MESH_HPP_
#define _REFLECT_NORMAL_SMOOTHED_MESH_HPP_

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
  No detailed.
  */
class NormalSmoothedMesh : public TriangleMesh 
{
 public:
  //! Create triangle mesh
  NormalSmoothedMesh(const Point3& vertex0, 
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
  void initialize(const Point3& vertex1, const Point3& vertex2);


  Point3 vertex_;
  Vector3 edge_[2]; // v0 to v1 and v0 to v2 edge vectors
  Vector3 vertex_normal_[3];
};

//! \} Geometry

} // namespace reflect

#endif // _REFLECT_NORMAL_SMOOTHED_MESH_HPP_
