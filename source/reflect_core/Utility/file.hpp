/*!
  \file file.hpp
  \author takemura
  */

#ifndef _REFLECT_FILE_HPP_
#define _REFLECT_FILE_HPP_

// Standard C++ library
#include <cstddef>

// Forward declaration
class QByteArray;

namespace reflect {

//! Write the data to QByteArray  
template <typename Type>
std::size_t write(QByteArray* array, const Type& value);

} // namespace reflect

#include "file-inl.hpp"

#endif // _REFLECT_FILE_HPP_
