/*!
  \file size.hpp
  \author takemura
  */

#ifndef _REFLECT_SIZE_HPP_
#define _REFLECT_SIZE_HPP_

// Standard C++ library
#include <cstddef>

namespace reflect {

//! \addtogroup Utility
//! \{

#define PRINT_CLASS_DATA(type) \
    reflect::printClassData<type>(#type)

#define PRINT_CL_DATA(type) \
    reflect::printClData<type>(#type)

#define PRINT_TYPE_DATA(type) \
    reflect::printTypeData<type>(0, #type)

#define PRINT_VARIABLE_DATA(variable) \
    reflect::printTypeData<decltype(variable)>(1, #variable)

//! Print class data
template <typename Type>
void printClassData(const char* name);

//! Print OpenCL data
template <typename Type>
void printClData(const char* name);

//! Print member data
template <typename Type>
std::size_t printMemberData();

//! Print type size and alignment
template <typename Type>
std::size_t printTypeData(const int indent_level, const char* name);
  
//! \} Utility

} // namespace reflect

#include "size-inl.hpp"

#endif // _REFLECT_SIZE_HPP_
