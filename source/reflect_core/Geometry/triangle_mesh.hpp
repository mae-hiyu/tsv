/*!
  \file triangle_mesh.hpp
  \author takemura
  */

#ifndef _REFLECT_TRIANGLE_MESH_HPP_
#define _REFLECT_TRIANGLE_MESH_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "geometry.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QString;

namespace reflect {

// Forward declaration
class Ray;

//! \addtogroup Geometry
//! \{

/*!
  \details
  No detailed.
  */
class TriangleMesh : public Geometry
{
 public:
  //! Print member variable data
  static std::size_t printMemberData();

  //! Set vertex texture coordinate
  void setTextureCoordinate(const Point2& texture_coordinate0,
                            const Point2& texture_coordinate1,
                            const Point2& texture_coordinate2);

  //! Calculate the texture coordinate using Barycentric coordinate system
  Point2 textureCoordinate(const double* barycentric) const;

 private:
  Point2 texture_coordinate_[3];
};

//! Calculate Barycentric coordinate
bool calculateBarycentricCoordinate(const Ray& ray,
                                    const Point3& vertex,
                                    const Vector3* edge,
                                    double* barycentric,
                                    double* t);

//! Make a polygon
std::vector<UniquePointer<Geometry>> makeTriangles(
    const QString& object_file_path,
    const bool is_enabled_smoothing,
    const bool is_nagata_patch);

//! \} Geometry

} // namespace reflect

#include "triangle_mesh-inl.hpp"

#endif // _REFLECT_TRIANGLE_MESH_HPP_
