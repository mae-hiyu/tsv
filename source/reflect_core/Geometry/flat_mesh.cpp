/*!
  \file flat_mesh.cpp
  \author takemura
  */

#include "flat_mesh.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "geometry.hpp"
#include "reflect_config.hpp"
#include "triangle_mesh.hpp"
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

namespace reflect  {

/*!
  \details
  No detailed.
  */
FlatMesh::FlatMesh(const Point3& vertex0,
                   const Point3& vertex1,
                   const Point3& vertex2) :
    vertex_{vertex0}
{
  initialize(vertex1, vertex2);
}

/*!
  \details
  No detailed.

  \return AABB
  */
Aabb FlatMesh::boundingBox() const
{
  auto min_point = vertex_.data();
  auto max_point = vertex_.data();
  Point3 mesh_points[] = {vertex_ + edge_[0], vertex_ + edge_[1]};
  for (const auto& point : mesh_points) {
    min_point = zisc::minElements(min_point, point.data());
    max_point = zisc::maxElements(max_point, point.data());
  }
  return Aabb{Point3{min_point}, Point3{max_point}};
}

/*!
  \details
  Please see the details of this algorithm below URL.
  http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-9-ray-triangle-intersection/m-ller-trumbore-algorithm/
  */
bool FlatMesh::isIntersected(const Ray& ray, IntersectionInfo* intersection) const
{
  double t;
  double barycentric[3];
  if (!calculateBarycentricCoordinate(ray, vertex_, edge_, barycentric, &t))
    return false;

  // Set point
  intersection->setPoint(ray.origin() + t * ray.direction());

  // Set normal
  const double cos_theta = zisc::dot(normal_, ray.direction());
  intersection->setReverseFace(cos_theta > 0.0);
  intersection->setNormal(normal_);

  // Set texture coordinate
  intersection->setTextureCoordinate(textureCoordinate(barycentric));

  return true;
}

/*!
  \details
  No detailed.
  */
std::size_t FlatMesh::printMemberData()
{
  std::size_t size = 0;
  size += TriangleMesh::printMemberData();
  size += PRINT_VARIABLE_DATA(vertex_);
  size += PRINT_VARIABLE_DATA(edge_);
  size += PRINT_VARIABLE_DATA(normal_);
  return size;
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> FlatMesh::samplePoint(Sampler& sampler) const
{
  double u = sampler.sample(0.0, 1.0);
  double v = sampler.sample(0.0, 1.0);
  if (u + v > 1.0) {
    u = 1.0 - u;
    v = 1.0 - v;
  }

  const auto point = vertex_ + u * edge_[0] + v * edge_[1];
  return std::make_pair(SampledPoint{point, surfaceArea()}, normal_);
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> FlatMesh::samplePoint(
    const IntersectionInfo& /* intersection */,
    Sampler& sampler) const
{
  return samplePoint(sampler);
}

/*!
  \details
  No detailed.
  */
void FlatMesh::transform(const Matrix4x4& matrix)
{
  affineTransform(matrix, &vertex_);
  affineTransform(matrix, &edge_[0]);
  affineTransform(matrix, &edge_[1]);
  affineTransform(matrix, &normal_);
  normal_ = normal_.normalized();

  const auto area = 0.5 * zisc::cross(edge_[0], edge_[1]).norm();
  setSurfaceArea(area);
}

// private member function

/*!
  \details
  No detailed.
  */
void FlatMesh::initialize(const Point3& vertex1, const Point3& vertex2)
{
  edge_[0] = vertex1 - vertex_;
  edge_[1] = vertex2 - vertex_;
  setNormal();
}

/*!
  \details
  No detailed.
  */
void FlatMesh::setNormal()
{
  normal_ = (zisc::cross(edge_[0], edge_[1])).normalized();
  REFLECT_CHECK_UNIT_VECTOR(normal_);
}

} // namespace reflect
