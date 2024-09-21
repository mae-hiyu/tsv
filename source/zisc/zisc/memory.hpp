/*!
  \file memory.hpp
  \author takemura
  */

#ifndef _ZISC_MEMORY_HPP_
#define _ZISC_MEMORY_HPP_

// Standard C++ library
#include <memory>

namespace zisc {

//! Make a unique pointer
template <typename Type, typename ...Types>
std::unique_ptr<Type> makeUnique(Types&& ...arguments);

} // namespace zisc

#include "memory-inl.hpp"

#endif // _ZISC_MEMORY_HPP_
