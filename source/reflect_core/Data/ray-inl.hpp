/*!
  \file ray-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RAY_INL_HPP_
#define _REFLECT_RAY_INL_HPP_

#include "ray.hpp"
// Standard C++ library
#include <cstddef>
#include <cstdint>
// Reflect
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
Ray::Ray() :
    is_alive_{false}
{
}

/*!
  \details
  No detailed.
  */
inline
Ray::Ray(const Point3& origin, const Vector3& direction) :
    origin_{origin},
    direction_{direction},
    is_alive_{true}
{
  setInverseDirection();
}

/*!
  \details
  No detailed.
  */
inline
const Vector3& Ray::direction() const
{
  return direction_;
}

/*!
  \details
  No detailed.
  */
inline
const Vector3& Ray::inverseDirection() const
{
  return inverse_direction_;
}

/*!
  \details
  No detailed.
  */
inline
bool Ray::isAlive() const
{
  return is_alive_;
}

/*!
  \details
  No detailed.
  */
inline
const Point3& Ray::origin() const
{
  return origin_;
}

/*!
  \details
  No detailed.
  */
inline
void Ray::setDirection(const Vector3& direction)
{
  direction_ = direction;
  setInverseDirection();
}

/*!
  \details
  No detailed.
  */
inline
void Ray::setInverseDirection()
{
  inverse_direction_[0] = (direction_[0] != 0.0) ? 1.0 / direction_[0] : 0.0;
  inverse_direction_[1] = (direction_[1] != 0.0) ? 1.0 / direction_[1] : 0.0;
  inverse_direction_[2] = (direction_[2] != 0.0) ? 1.0 / direction_[2] : 0.0;

  sign_[0] = (inverse_direction_[0] < 0.0) ? 1 : 0;
  sign_[1] = (inverse_direction_[1] < 0.0) ? 1 : 0;
  sign_[2] = (inverse_direction_[2] < 0.0) ? 1 : 0;
}

/*!
  \details
  No detailed.
  */
inline
void Ray::setOrigin(const Point3& origin)
{
  origin_ = origin;
}

/*!
  \details
  No detailed.
  */
inline
void Ray::setAlive(const bool is_alive)
{
  is_alive_ = is_alive;
}

/*!
  \details
  No detailed.
  */
inline
const std::uint8_t* Ray::sign() const
{
  return sign_;
}

} // namespace reflect

#endif // _REFLECT_RAY_INL_HPP_
