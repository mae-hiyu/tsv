/*!
  \file object-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_OBJECT_INL_HPP_
#define _REFLECT_OBJECT_INL_HPP_

#include "object.hpp"
// Reflect
#include "Geometry/geometry.hpp"
#include "Material/material.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
const Geometry& Object::geometry() const
{
  return *geometry_;
}

/*!
  \details
  No detailed.
  */
inline
const Material& Object::material() const
{
  return material_;
}

/*!
  \details
  No detailed.
  */
inline
bool isSameObject(const Object* object1, const Object* object2)
{
  return object1 == object2;
}

} // namespace reflect

#endif // _REFLECT_OBJECT_INL_HPP_
