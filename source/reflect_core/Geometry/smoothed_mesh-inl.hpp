/*!
  \file smoothed_mesh-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SMOOTHED_MESH_INL_HPP_
#define _REFLECT_SMOOTHED_MESH_INL_HPP_

#include "smoothed_mesh.hpp"
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

using zisc::treatAs;

/*!
  \details
  No detailed.
  */
inline
Vector3 SmoothedMesh::normal(const double eta, const double xi) const
{
  const auto x1 = c_[1] + c_[3] * xi + 2.0 * c_[4] * eta;
  const auto x2 = c_[2] + c_[3] * eta + 2.0 * c_[5] * xi;
  return zisc::cross(x1, x2).normalized();
}

/*!
  \details
  No detailed.
  */
inline
Point3 SmoothedMesh::point(const double eta, const double xi) const
{
  const auto point = c_[0] + c_[1] * eta + c_[2] * xi + c_[3] * eta * xi +
                     c_[4] * (eta * eta) + c_[5] * (xi * xi);
  return *treatAs<const Point3*>(&point);
}

} // namespace reflect

#endif // _REFLECT_SMOOTHED_MESH_INL_HPP_
