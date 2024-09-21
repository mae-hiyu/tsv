/*!
  \file vector.hpp
  \author takemura
  */

#ifndef _REFLECT_VECTOR_HPP_
#define _REFLECT_VECTOR_HPP_

// Zisc
#include "zisc/vector.hpp"

namespace reflect {

//! \addtogroup LinearAlgebra
//! \{

using Vector3 = zisc::Vector<double, 3>;

//! Change basis of vector
void changeBasis(const Vector3& z, Vector3* vector);

//! \} LinearAlgebra

} // namespace reflect

#endif // _REFLECT_VECTOR_HPP_
