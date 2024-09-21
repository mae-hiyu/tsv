/*!
 \file ray.hpp
 \author takemura
 */

#ifndef _REFLECT_RAY_HPP_
#define _REFLECT_RAY_HPP_

// Standard C++ library
#include <cstddef>
#include <cstdint>
// Reflect
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

//! \addtogroup Data
//! \{

/*!
  \details
  No detailed.
  */
class Ray
{
 public:
  //! Create a dead ray
  Ray();

  //! Create ray
  Ray(const Point3& origin, const Vector3& direction);


  //! Return the direction
  const Vector3& direction() const;

  //! Return the inverse direction vector
  const Vector3& inverseDirection() const;

  //! Check if the ray is alive
  bool isAlive() const;

  //! Return the origin
  const Point3& origin() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Set ray alival
  void setAlive(const bool is_alive);

  //! Set ray direction
  void setDirection(const Vector3& direction);

  //! Set ray origin
  void setOrigin(const Point3& origin);

  //! Return the direction sign
  const std::uint8_t* sign() const;

 private:
  //! Set inverse direction.
  void setInverseDirection();

  Point3 origin_;
  Vector3 direction_,
          inverse_direction_;
  std::uint8_t sign_[3];
  bool is_alive_;
};

//! \} Data

} // namespace reflect

#include "ray-inl.hpp"

#endif // _REFLECT_RAY_HPP_
