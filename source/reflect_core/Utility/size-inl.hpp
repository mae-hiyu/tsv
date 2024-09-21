/*!
  \file size-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SIZE_INL_HPP_
#define _REFLECT_SIZE_INL_HPP_

#include "size.hpp"
// Standard C++ library
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <type_traits>

namespace reflect {

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void printClassData(const char* name)
{
  printTypeData<Type>(0, name);
  constexpr std::size_t size = sizeof(Type);
  std::size_t padding = size - Type::printMemberData();
  if (std::is_polymorphic<Type>::value)
    padding -= sizeof(void*);
  std::cout << "  " << std::setw(20) << std::left << "  Padding" 
            << ",," << padding << "," << std::endl;
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void printClData(const char* name)
{
  printTypeData<Type>(0, name);
  constexpr std::size_t size = sizeof(Type);
  const std::size_t padding = size - printMemberData<Type>();
  std::cout << "  Padding: " << padding << std::endl;
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
std::size_t printTypeData(const int indent_level, const char* name)
{
  if (indent_level == 0) {
    std::cout << std::setw(20) << std::left << name << ",,";
  }
  else {
    std::string indent;
    for (int level = 0; level < indent_level; ++level)
      indent += "  ";
    std::cout << indent << "," << std::setw(20) << std::left << name << "," ;
  }
  constexpr int size = static_cast<int>(sizeof(Type));
  constexpr int alignment = static_cast<int>(std::alignment_of<Type>::value);
  std::cout << std::setw(3) << size << ","
            << std::setw(3) << alignment << std::endl;
  return size;
}

} // namespace reflect

#endif // _REFLECT_SIZE_INL_HPP_
