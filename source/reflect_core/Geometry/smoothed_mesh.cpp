/*!
  \file smoothed_mesh.cpp
  \author takemura
  */

#include "smoothed_mesh.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>
// Zisc
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "geometry.hpp"
#include "triangle_mesh.hpp"
#include "Data/intersection_info.hpp"
#include "Data/ray.hpp"
#include "DataStructure/aabb.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "LinearAlgebra/transformation.hpp"
#include "Sampling/sampled_point.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/size.hpp"

namespace reflect {

using zisc::cast;
using zisc::treatAs;

// Calculate curvature parameter
Vector3 calculateCurvatureParameter(const Vector3& distance,
                                    const Vector3& normal0,
                                    const Vector3& normal1);

// Calculate surface parameters
bool calculateSurfaceParameter(const double* a,
                               const double* b,
                               const double* r,
                               double* eta,
                               double* xi,
                               double* t);

/*!
  \details
  No detailed.
  */
SmoothedMesh::SmoothedMesh(const Point3& vertex0,
                           const Point3& vertex1,
                           const Point3& vertex2,
                           const Vector3& normal0,
                           const Vector3& normal1,
                           const Vector3& normal2)
{
  initialize(vertex0, vertex1, vertex2, normal0, normal1, normal2);
}

/*!
  \details
  No detailed.
  */
Aabb SmoothedMesh::boundingBox() const
{
  const auto v0 = point(0.0, 0.0);
  const auto v1 = point(1.0, 0.0);
  const auto v2 = point(1.0, 1.0);
  const auto n0 = normal(0.0, 0.0);
  const auto n1 = normal(1.0, 0.0);
  const auto n2 = normal(1.0, 1.0);

  auto min_point = zisc::minElements(v0.data(), v1.data());
  auto max_point = zisc::maxElements(v0.data(), v1.data());
  min_point = zisc::minElements(min_point, v2.data());
  max_point = zisc::maxElements(max_point, v2.data());

  const Vector3 distance[3] = {v1 - v0, v2 - v1, v2 - v0};
  const Vector3 curvature[3] = {calculateCurvatureParameter(distance[0], n0, n1),
                                calculateCurvatureParameter(distance[1], n1, n2),
                                calculateCurvatureParameter(distance[2], n0, n2)};
  const Point3* vertices[3] = {&v0, &v1, &v0};

  const auto edge_point = 
  [&vertices, &distance, &curvature](const std::size_t i, const double xi)
  {
    return *vertices[i] + (distance[i] - curvature[i]) * xi + 
           curvature[i] * (xi * xi);
  };

  const auto calculate_xi = 
  [&distance, &curvature](const std::size_t i, const std::size_t j, double* xi)
  {
    if (curvature[i][j] == 0.0)
      return false;
    const auto x =  -(distance[i][j] - curvature[i][j]) / (2.0 * curvature[i][j]);
    if (!((0.0 <= x) && (x <= 1.0)))
      return false;
    *xi = x;
    return true;
  };

  const auto calculate_parameter = 
  [this](const std::size_t j, double* eta, double* xi)
  {
    const zisc::Matrix<double, 2, 2> matrix{2.0 * c_[4][j], c_[3][j],
                                            c_[3][j], 2.0 * c_[5][j]};
    if (matrix.determinant() == 0.0)
      return false;
    const auto inverse_matrix = matrix.inverseMatrix();
    const zisc::Matrix<double, 2, 1> c{c_[1][j],
                                       c_[2][j]};
    const auto result = inverse_matrix * c;
    const double e = result(0, 0);
    const double x = result(1, 0);
    if (!((0.0 <= x) && (x <= e) && (e <= 1.0)))
      return false;

    *eta = e;
    *xi = x;
    return true;
  };

  double eta,
         xi;
  for (std::size_t j = 0; j < 3; ++j) {
    for (std::size_t i = 0; i < 3; ++i) {
      if (calculate_xi(i, j, &xi)) {
        const auto point = edge_point(i, xi);
        min_point = zisc::minElements(min_point, point.data());
        max_point = zisc::maxElements(max_point, point.data());
      }
    }
    if (calculate_parameter(j, &eta, &xi)) {
      const auto point = this->point(eta, xi);
      min_point = zisc::minElements(min_point, point.data());
      max_point = zisc::maxElements(max_point, point.data());
    }
  }

  return Aabb{Point3{min_point}, Point3{max_point}};
}

/*!
  \details
  No detailed.
  */
bool SmoothedMesh::isIntersected(const Ray& ray, 
                                 IntersectionInfo* intersection) const
{
  const auto& e3 = ray.direction();
  const auto e1 = zisc::cross(e3, c_[5]).normalized();
  const auto e2 = zisc::cross(e3, e1);

  const double a[5] = {
      zisc::dot(e1, c_[0] - *treatAs<const Vector3*>(&ray.origin())), // a00
      zisc::dot(e1, c_[1]), // a10
      zisc::dot(e1, c_[2]), // a01
      zisc::dot(e1, c_[3]), // a11
      zisc::dot(e1, c_[4])}; // a20
  const double b[6] = {
      zisc::dot(e2, c_[0] - *treatAs<const Vector3*>(&ray.origin())), // b00
      zisc::dot(e2, c_[1]), // b10
      zisc::dot(e2, c_[2]), // b01
      zisc::dot(e2, c_[3]), // b11
      zisc::dot(e2, c_[4]), // b20
      zisc::dot(e2, c_[5])}; // b02
  const double r[6] = {
      zisc::dot(e3, c_[0] - *treatAs<const Vector3*>(&ray.origin())), // r00
      zisc::dot(e3, c_[1]), // r10
      zisc::dot(e3, c_[2]), // r01
      zisc::dot(e3, c_[3]), // r11
      zisc::dot(e3, c_[4]), // r20
      zisc::dot(e3, c_[5])}; // r02

  double eta,
         xi,
         t;
  if (!calculateSurfaceParameter(a, b, r, &eta, &xi, &t))
    return false;

  // Set point
  intersection->setPoint(ray.origin() + t * ray.direction());

  // Set normal
  const auto normal = this->normal(eta, xi);
  const double cos_theta = zisc::dot(normal, ray.direction());
  intersection->setReverseFace(cos_theta > 0.0);
  intersection->setNormal(normal);

  // Set texture coordinate
  double barycentric[3] = {1.0 - eta, eta - xi, xi};
  intersection->setTextureCoordinate(textureCoordinate(barycentric));

  return true;
}

/*!
  \details
  No detailed.
  */
std::size_t SmoothedMesh::printMemberData()
{
  std::size_t size = 0;
  size += TriangleMesh::printMemberData();
  size += PRINT_VARIABLE_DATA(c_);
  return size;
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> SmoothedMesh::samplePoint(Sampler& /* sampler */) const
{
  zisc::raiseError("## SmoothedMesh class does'nt support \"samplePoint\" method.");
  return std::make_pair(SampledPoint{Point3{}, 0.0}, Vector3{});
}

/*!
  \details
  No detailed.
  */
std::pair<SampledPoint, Vector3> SmoothedMesh::samplePoint(
    const IntersectionInfo& /* intersection */,
    Sampler& /* sampler */) const
{
  zisc::raiseError("## SmoothedMesh class does'nt support \"samplePoint\" method.");
  return std::make_pair(SampledPoint{Point3{}, 0.0}, Vector3{});
}

/*!
  \details
  No detailed.
  */
void SmoothedMesh::transform(const Matrix4x4& matrix)
{
  affineTransform(matrix, treatAs<Point3*>(&c_[0]));
  for (std::size_t i = 1; i < 6; ++i)
    affineTransform(matrix, &c_[i]);
}

/*!
  \details
  No detailed.
  */
void SmoothedMesh::initialize(const Point3& vertex0,
                              const Point3& vertex1,
                              const Point3& vertex2,
                              const Vector3& normal0,
                              const Vector3& normal1,
                              const Vector3& normal2)
{
  const Vector3 distance[3] = {vertex1 - vertex0,
                               vertex2 - vertex1,
                               vertex2 - vertex0};
  const Vector3 curvature[3] = {
      calculateCurvatureParameter(distance[0], normal0, normal1),
      calculateCurvatureParameter(distance[1], normal1, normal2),
      calculateCurvatureParameter(distance[2], normal0, normal2)};

  c_[0] = *treatAs<const Vector3*>(&vertex0); // c00
  c_[1] = distance[0] - curvature[0]; // c10
  c_[2] = distance[1] + curvature[0] - curvature[2]; // c01
  c_[3] = curvature[2] - curvature[0] - curvature[1]; // c11
  c_[4] = curvature[0]; // c20
  c_[5] = curvature[1]; // c02
}

/*!
  \details
  No detailed.
  */
Vector3 calculateCurvatureParameter(const Vector3& distance,
                                    const Vector3& normal0,
                                    const Vector3& normal1)
{
  const auto delta_v = (normal0 - normal1) * 0.5;
  const auto delta_c = zisc::dot(normal0, delta_v);

  const auto c = 1.0 - 2.0 * delta_c;
  if (std::abs(c) == 1.0)
    return Vector3{};

  const auto v = (normal0 + normal1) * 0.5;
  const auto delta_d = zisc::dot(distance, delta_v);
  const auto d = zisc::dot(distance, v);
  return (delta_d / (1.0 - delta_c)) * v + (d / delta_c) * delta_v;
}

/*!
  \details
  No detailed.
  */
bool calculateSurfaceParameter(const double* a,
                               const double* b,
                               const double* r,
                               double* eta,
                               double* xi,
                               double* t)
{
  std::size_t count = 0;
  double eta_list[4];
  double xi_list[4];
  // a01 + a11 * eta -> nonzero
  if (a[2] != 0.0 || a[3] != 0.0) {
    const double u[4] = {a[3] * b[4] - a[4] * b[3],
                         a[3] * b[1] - a[1] * b[3] + a[2] * b[4] - a[4] * b[2],
                         a[2] * b[1] - a[1] * b[2] + a[3] * b[0] - a[0] * b[3],
                         a[2] * b[0] - a[0] * b[2]};
    const double m = a[3] * u[0] + a[4] * a[4] * b[5],
                 n = a[2] * u[0] + a[3] * u[1] + 2.0 * a[1] * a[4] * b[5],
                 o = a[2] * u[1] + a[3] * u[2] + 
                     b[5] * (a[1] * a[1] + 2.0 * a[0] * a[4]),
                 p = a[2] * u[2] + a[3] * u[3] + 2.0 * a[0] * a[1] * b[5],
                 q = a[2] * u[3] + a[0] * a[0] * b[5];
    std::size_t num = 0;
    double e[4];
    zisc::solveQuarticEquation(m, n, o, p, q, &num, e);

    for (std::size_t i = 0; i < num; ++i) {
      if ((0.0 <= e[i]) && (e[i] <= 1.0)) {
        const double t1 = a[2] + a[3] * e[i];
        const double t2 = a[0] + a[1] * e[i] + a[4] * e[i] * e[i];
        const double x = -t2 / t1;
        if ((0.0 <= x) && (x <= e[i])) {
          eta_list[count] = e[i];
          xi_list[count] = x;
          ++count;
        }
      }
    }
  }
  // a01 + a11 * eta -> zero
  else {
    zisc::raiseError("## a01 and a11 are zero.");
    return false;
  }

  if (count == 0)
    return false;

  // Chose the closest intersection point
  std::size_t index = std::numeric_limits<std::size_t>::max();
  double lambda = std::numeric_limits<double>::max();
  for (std::size_t i = 0; i < count; ++i) {
    const double e = eta_list[i];
    const double x = xi_list[i];
    const double l = r[0] + r[1] * e + r[2] * x + r[3] * e * x + 
                     r[4] * e * e + r[5] * x * x;
    if ((0.0 < l) && (l < lambda)) {
      lambda = l;
      index = i;
    }
  }

  if (index == std::numeric_limits<std::size_t>::max())
    return false;

  *eta = eta_list[index];
  *xi = xi_list[index];
  *t = lambda;

  return true;
}

} // namespace reflect
