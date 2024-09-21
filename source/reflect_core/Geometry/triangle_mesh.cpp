/*!
  \file triangle_mesh.cpp
  \author takemura
  */

#include "triangle_mesh.hpp"
// Standard C++ library
#include <cstddef>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
// Qt
#include <QFileInfo>
#include <QString>
// Zisc
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/string.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "flat_mesh.hpp"
#include "geometry.hpp"
#include "normal_smoothed_mesh.hpp"
#include "reflect_config.hpp"
#include "smoothed_mesh.hpp"
#include "Data/ray.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "LinearAlgebra/transformation.hpp"
#include "Utility/floating_point.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect  {

/*!
  \details
  No detailed.
  */
std::size_t TriangleMesh::printMemberData()
{
  std::size_t size = 0;
  size += Geometry::printMemberData();
  size += PRINT_VARIABLE_DATA(texture_coordinate_);
  return size;
}

/*!
  \details
  No detailed.
  */
bool calculateBarycentricCoordinate(const Ray& ray,
                                    const Point3& vertex,
                                    const Vector3* edge,
                                    double* barycentric,
                                    double* t)
{
  const auto direction = ray.origin() - vertex;
  const auto q = zisc::cross(direction, edge[0]);
  const auto p = zisc::cross(ray.direction(), edge[1]);
  const double inverse_determinant = 1.0 / zisc::dot(p, edge[0]);

  // The time that tye ray intersects with this triangle
  const double time = inverse_determinant * zisc::dot(q, edge[1]);
  if (time <= 0.0)
    return false;

  const double u = inverse_determinant * zisc::dot(p, direction);
  if (u < 0.0 || 1.0 < u)
    return false;
  const double v = inverse_determinant * zisc::dot(q, ray.direction());
  if (v < 0.0 || 1.0 < v)
    return false;
  if ((u + v) > 1.0)
    return false;

  barycentric[0] = u;
  barycentric[1] = v;
  barycentric[2] = 1.0 - (u + v);
  *t = time;
  return true;
}

/*!
  \details
  No detailed.
  */
std::vector<UniquePointer<Geometry>> makeTrianglesFromWavefront(
    const QString& object_file_path,
    const bool is_enabled_smoothing,
    const bool /* is_nagata_patch */)
{
  std::ifstream object_file{object_file_path.toStdString()};

  std::string keyword;
  char delimiter;
  bool smoothing = false;
  bool has_texture_coordinate = false,
       has_vertex_normal = false;
  bool first_mesh = true;
  std::size_t line_number = 1;
  std::list<Point3> vertexes;
  std::list<Vector3> normals;
  std::list<Point2> texture_coordinates;
  std::vector<const Point3*> vertex_reference;
  std::vector<const Point2*> texture_coordinate_reference;
  std::vector<const Vector3*> normal_reference;
  std::list<Geometry*> meshes;
  double x,
         y,
         z;

  for (std::string line; std::getline(object_file, line); ++line_number) {
    // Skip empty or comment line
    line = zisc::trim(line);
    if (line == "" || line[0] == '#')
      continue;

    std::istringstream buffer{line};
    buffer >> keyword;
    // Material name
    if (keyword == "mtllib") {
      continue;
    }
    // Material name
    else if (keyword == "usemtl") {
      continue;
    }
    // Group name
    else if (keyword == "g") {
      continue;
    }
    // Object name
    else if (keyword == "o") {
      continue;
    }
    // Vertex point
    else if (keyword == "v") {
      buffer >> x >> y >> z;
      vertexes.emplace_back(x, y, z);
    }
    // Vertex normal
    else if (keyword == "vn") {
      has_vertex_normal = true;
      buffer >> x >> y >> z;
      normals.emplace_back(Vector3{x, y, z}.normalized());
    }
    // Texture-coordinate
    else if (keyword == "vt") {
      has_texture_coordinate = true;
      buffer >> x >> y;
      texture_coordinates.emplace_back(x, 1.0 - y);
    }
    // Smoothing
    else if (keyword == "s") {
      std::string value;
      buffer >> value;
      smoothing = is_enabled_smoothing && (value == "1");
    }
    else if (keyword == "f") {
      std::size_t vertex_index[3];
      std::size_t texture_index[3];
      std::size_t normal_index[3];
      if (first_mesh) {
        // Make vertex reference list
        vertex_reference.reserve(vertexes.size());
        for (const auto& vertex : vertexes)
          vertex_reference.emplace_back(&vertex);
        // Make vertex normal reference list
        normal_reference.reserve(normals.size());
        for (const auto& normal : normals)
          normal_reference.emplace_back(&normal);
        // Make texture coordinate reference list
        texture_coordinate_reference.reserve(texture_coordinates.size());
        for (const auto& coordinate : texture_coordinates)
          texture_coordinate_reference.emplace_back(&coordinate);

        first_mesh = false;
      }
      if (has_texture_coordinate && has_vertex_normal) {
        for (std::size_t index = 0; index < 3; ++index) {
          buffer >> vertex_index[index] >> delimiter
                 >> texture_index[index] >> delimiter
                 >> normal_index[index];
        }
      }
      else if (!has_texture_coordinate && has_vertex_normal) {
        for (std::size_t index = 0; index < 3; ++index) {
          buffer >> vertex_index[index] >> delimiter >> delimiter
                 >> normal_index[index];
        }
      }
      else if (has_texture_coordinate && !has_vertex_normal) {
        for (std::size_t index = 0; index < 3; ++index)
          buffer >> vertex_index[index] >> delimiter >> texture_index[index];
      }
      else if (!has_texture_coordinate && !has_vertex_normal) {
        for (std::size_t index = 0; index < 3; ++index)
          buffer >> vertex_index[index];
      }
      TriangleMesh* mesh = nullptr;
//      if (!smoothing) {
        mesh = new FlatMesh{*(vertex_reference[vertex_index[0] - 1]),
                            *(vertex_reference[vertex_index[1] - 1]),
                            *(vertex_reference[vertex_index[2] - 1])};
//      }
//      else if (!is_nagata_patch) {
//        mesh = new NormalSmoothedMesh{*(vertex_reference[vertex_index[0] - 1]),
//                                      *(vertex_reference[vertex_index[1] - 1]),
//                                      *(vertex_reference[vertex_index[2] - 1]),
//                                      *(normal_reference[normal_index[0] - 1]),
//                                      *(normal_reference[normal_index[1] - 1]),
//                                      *(normal_reference[normal_index[2] - 1])};
//      }
//      else {
//        mesh = new SmoothedMesh{*(vertex_reference[vertex_index[0] - 1]),
//                                *(vertex_reference[vertex_index[1] - 1]),
//                                *(vertex_reference[vertex_index[2] - 1]),
//                                *(normal_reference[normal_index[0] - 1]),
//                                *(normal_reference[normal_index[1] - 1]),
//                                *(normal_reference[normal_index[2] - 1])};
//      }
      if (has_texture_coordinate) {
        mesh->setTextureCoordinate(
            *(texture_coordinate_reference[texture_index[0] - 1]),
            *(texture_coordinate_reference[texture_index[1] - 1]),
            *(texture_coordinate_reference[texture_index[2] - 1]));
      }
      meshes.emplace_back(mesh);
    }
    else {
      zisc::raiseError("MeashError: In \"", object_file_path.toStdString(),
                       "\" line ", line_number, ": unsupported syntax.");
    }
  }
  std::vector<UniquePointer<Geometry>> mesh_list;
  mesh_list.reserve(meshes.size());
  for (auto* mesh : meshes)
    mesh_list.emplace_back(mesh);
  return std::move(mesh_list);
}

/*!
  \details
  No detailed.
  */
std::vector<UniquePointer<Geometry>> makeTriangles(
    const QString& object_file_path,
    const bool is_enabled_smoothing,
    const bool is_nagata_patch)
{
  const QFileInfo file_info{object_file_path};
  const auto suffix = file_info.suffix();
  if (suffix == "obj") {
    return makeTrianglesFromWavefront(object_file_path, 
                                      is_enabled_smoothing, 
                                      is_nagata_patch);
  }
  else {
    zisc::raiseError("TriangleMeshError: \"", object_file_path.toStdString(), 
                     "\" is not supported format.");
  }
  return std::vector<UniquePointer<Geometry>>{};
}

} // namespace reflect 
