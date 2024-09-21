/*!
  \file light_source_reference.hpp
  \author takemura
  */

#ifndef _REFLECT_LIGHT_SOURCE_REFERENCE_HPP_
#define _REFLECT_LIGHT_SOURCE_REFERENCE_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>

namespace reflect {

// Forward declaration
class Object;

//! \addtogroup Data
//! \{

/*!
  \details
  No detailed.
  */
class LightSourceReference
{
 public:
  //! Create a light source reference
  LightSourceReference(const double total_flux, const Object* light_source);


  //! Return the inverse weight of this light source
  double inverseWeight() const;

  //! Return the light source object
  const Object* object() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the weight of this light sonrce in the scene
  double weight() const;

 private:
  //! Initialize
  void initialize(const double total_flux);


  double weight_,
         inverse_weight_;
  const Object* light_source_;
};

//! \} Data

} // namespace reflect

#include "light_source_reference-inl.hpp"

#endif // _REFLECT_LIGHT_SOURCE_REFERENCE_HPP_
