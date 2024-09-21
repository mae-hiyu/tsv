/*!
  \file memory-inl.hpp
  \author takemura
  */

#ifndef _ZISC_MEMORY_INL_HPP_
#define _ZISC_MEMORY_INL_HPP_

#include "memory.hpp"
// Standard C++ library
#include <memory>
#include <utility>

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Type, typename ...Types> inline
std::unique_ptr<Type> makeUnique(Types&& ...arguments)
{
  return std::unique_ptr<Type>{new Type{std::forward<Types>(arguments)...}};
}

} // namespace zisc

#endif // _ZISC_MEMORY_INL_HPP_
