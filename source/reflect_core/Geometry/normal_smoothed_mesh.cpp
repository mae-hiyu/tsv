/*!
  \file normal_smoothed_mesh.cpp
  \author takemura
  */

#include "normal_smoothed_mesh.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
// Zisc
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/string.hpp"
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
NormalSmoothedMesh::NormalSmoothedMesh(const Point3& vertex0,
                                       const Point3& vertex1,
                                       const Point3& vertex2,
                                       const Vector3& normal0,
                                       const Vector3& normal1,
                                       const Vector3& normal2) :
    vertex_{vertex0},
    vertex_normal_{normal0, normal1, normal2}
{
  initialize(vertex1, vertex2);
}

/*!
  \details
  No detailed.

  \return AABB
  */
Aabb NormalSmoothedMesh::boundingBox() const
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
bool NormalSmoothedMesh::isIntersected(const Ray& ray, 
                                       IntersectionInfo* intersection) const
{
  double t;
  double barycentric[3];
  if (!calculateBarycentricCoordinate(ray, vertex_, edge_, barycentric, &t))
    return false;

  // Set point
  intersection->setPoint(ray.origin() + t * ray.direction());

  // Set normal
  const auto smoothed_normal = barycentric[2] * vertex_normal_[0] +
                               barycentric[0] * vertex_normal_[1] +
                               barycentric[1] * vertex_normal_[2];
  const double cos_theta = zisc::dot(smoothed_normal, ray.direction());
  intersection->setReverseFace(cos_theta > 0.0);
  intersection->setNormal(smoothed_normal);

  // Set texture coordinate
  intersection->setTextureCoordinate(textureCoordinate(barycentric));

  return true;
}

/*!
  \details
  No detailed.
  */
std::size_t NormalSmoothedMesh::printMemberData()
{
  std::size_t size = 0;
  size += TriangleMesh::printMemberData();
  size += PRINT_VARIABLE_DATA(vertex_);
  size += PRINT_VARIABLE_DATA(edge_);
  size += PRINT_VARIABLE_DATA(vertex_normal_);
  return size;
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> NormalSmoothedMesh::samplePoint(
    Sampler& sampler) const
{
  const double u = sampler.sample(0.0, 1.0);
  const double v = sampler.sample(0.0, 1.0);

  double barycentric[3];
  barycentric[0] = (u + v <= 1.0) ? u : 1.0 - u;
  barycentric[1] = (u + v <= 1.0) ? v : 1.0 - v;
  barycentric[2] = 1.0 - (u + v);

  const auto point = vertex_ + barycentric[0] * edge_[0] + barycentric[1] * edge_[1];
  const auto smoothed_normal = barycentric[2] * vertex_normal_[0] +
                               barycentric[0] * vertex_normal_[1] +
                               barycentric[1] * vertex_normal_[2];

  return std::make_pair(SampledPoint{point, surfaceArea()}, smoothed_normal);
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> NormalSmoothedMesh::samplePoint(
    const IntersectionInfo& /* intersection */,
    Sampler& sampler) const
{
  return samplePoint(sampler);
}

/*!
  \details
  No detailed.
  */
void NormalSmoothedMesh::transform(const Matrix4x4& matrix)
{
  affineTransform(matrix, &vertex_);
  affineTransform(matrix, &edge_[0]);
  affineTransform(matrix, &edge_[1]);
  affineTransform(matrix, &vertex_normal_[0]);
  affineTransform(matrix, &vertex_normal_[1]);
  affineTransform(matrix, &vertex_normal_[2]);
  for (auto& normal : vertex_normal_)
    normal = normal.normalized();

  const auto area = 0.5 * zisc::cross(edge_[0], edge_[1]).norm();
  setSurfaceArea(area);
}

// private member function

/*!
  \details
  No detailed.
  */
void NormalSmoothedMesh::initialize(const Point3& vertex1, const Point3& vertex2)
{
  edge_[0] = vertex1 - vertex_;
  edge_[1] = vertex2 - vertex_;
}

} // Namespace reflect
