/*!
  \file file-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_FILE_INL_HPP_
#define _REFLECT_FILE_INL_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Qt
#include <QByteArray>

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <typename Type> inline
std::size_t write(QByteArray* array, const Type& value)
{
  constexpr int size = cast<int>(sizeof(Type));
  const char* data = zisc::treatAs<const char*>(&value);
  array->append(data, size);

  return sizeof(Type);
}

} // namespace reflect

#endif // _REFLECT_FILE_INL_HPP_
