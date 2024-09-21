/*!
  \file tonemapping_method-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_TONEMAPPING_METHOD_INL_HPP_
#define _REFLECT_TONEMAPPING_METHOD_INL_HPP_

#include "tonemapping_method.hpp"
// Reflect
#include "LinearAlgebra/transformation.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
double TonemappingMethod::inverseGamma() const
{
  return inverse_gamma_;
}

/*!
  \details
  No detailed.
  */
inline
const Matrix3x3& TonemappingMethod::toRgbMatrix() const
{
  return to_rgb_matrix_;
}

/*!
  \details
  No detailed.
  */
inline
const Matrix3x3& TonemappingMethod::toXyzMatrix() const
{
  return to_xyz_matrix_;
}

} // namespace reflect

#endif // _REFLECT_TONEMAPPING_METHOD_INL_HPP_
