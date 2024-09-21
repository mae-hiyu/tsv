/*!
  \file triangle_mesh-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_TRIANGLE_MESH_INL_HPP_
#define _REFLECT_TRIANGLE_MESH_INL_HPP_

#include "triangle_mesh.hpp"
// Reflect
#include "LinearAlgebra/point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
void TriangleMesh::setTextureCoordinate(const Point2& texture_coordinate0,
                                        const Point2& texture_coordinate1,
                                        const Point2& texture_coordinate2)
{
  texture_coordinate_[0] = texture_coordinate0;
  texture_coordinate_[1] = texture_coordinate1;
  texture_coordinate_[2] = texture_coordinate2;
}

/*!
  \details
  No detailed.
  */
inline
Point2 TriangleMesh::textureCoordinate(const double* barycentric) const
{
  Point2 texture_coordinate;
  for (std::size_t index = 0; index < 2; ++index) {
    texture_coordinate[index] = barycentric[2] * texture_coordinate_[0][index] +
                                barycentric[0] * texture_coordinate_[1][index] +
                                barycentric[1] * texture_coordinate_[2][index];
  }
  return texture_coordinate;
}

} // namespace reflect

#endif // _REFLECT_TRIANGLE_MESH_INL_HPP_
