/*!
  \file light_source_reference-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_LIGHT_SOURCE_REFERENCE_INL_HPP_
#define _REFLECT_LIGHT_SOURCE_REFERENCE_INL_HPP_

#include "light_source_reference.hpp"

namespace reflect {

// Forward declaration
class Object;

/*!
  \details
  No detailed.
  */
inline
double LightSourceReference::inverseWeight() const
{
  return inverse_weight_;
}

/*!
  \details
  No detailed.
  */
inline
const Object* LightSourceReference::object() const
{
  return light_source_;
}

/*!
  \details
  No detailed.
  */
inline
double LightSourceReference::weight() const
{
  return weight_;
}

} // namespace reflect

#endif // _REFLECT_LIGHT_SOURCE_REFERENCE_INL_HPP_
