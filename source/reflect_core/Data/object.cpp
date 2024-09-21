/*!
 \file object.cpp
 \author takemura
 */

#include "object.hpp"
// Standard C++ library
#include <cstddef>
// Reflect
#include "Geometry/geometry.hpp"
#include "Material/material.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
Object::Object(const Material& material, UniquePointer<Geometry>&& geometry) :
    material_{material},
    geometry_{std::move(geometry)}
{
}

/*!
  \details
  No detailed.
  */
Object::Object(Object&& object) :
    material_{object.material_},
    geometry_{std::move(object.geometry_)}
{
}

/*!
  \details
  No detailed.
  */
std::size_t Object::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(material_);
  size += PRINT_VARIABLE_DATA(geometry_);
  return size;
}

} // namespace reflect
