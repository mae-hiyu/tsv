/*!
 \file material-inl.hpp
 \author takemura
 */

#ifndef _REFLECT_MATERIAL_INL_HPP_
#define _REFLECT_MATERIAL_INL_HPP_

#include "material.hpp"

namespace reflect {

// Forward declaration
class EmitterModel;
class SurfaceModel;

/*!
  \details
  No detailed.
  */
inline
const SurfaceModel& Material::surface() const
{
  return *surface_;
}

/*!
  \details
  No detailed.
  */
inline
bool Material::isLightSource() const
{
  return emitter_ != nullptr;
}

/*!
 \details
 No detailed.
 */
inline
const EmitterModel& Material::emitter() const
{
  return *emitter_;
}
  
} // namespace reflect

#endif // _REFLECT_MATERIAL_INL_HPP_
