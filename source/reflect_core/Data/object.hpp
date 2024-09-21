/*!
 \file object.hpp
 \author takemura
 */

#ifndef _REFLECT_OBJECT_HPP_
#define _REFLECT_OBJECT_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Reflect
#include "Geometry/geometry.hpp"
#include "Material/material.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

//! \addtogroup Data
//! \{

/*!
  \details
  No detailed.
  */
class Object
{
 public:
  //! Create object
  Object(const Material& material, UniquePointer<Geometry>&& geometry);

  //! Move object
  Object(Object&& object);


  //! Get geometry 
  const Geometry& geometry() const;

  //! Get material
  const Material& material() const;

  //! Print member variable data
  static std::size_t printMemberData();

 private:
  Material material_;
  UniquePointer<Geometry> geometry_;
};

//! Check two objects are same
bool isSameObject(const Object* object1, const Object* object2);

//! \} Data

} // namespace reflect

#include "object-inl.hpp"

#endif // _REFLECT_OBJECT_HPP_
