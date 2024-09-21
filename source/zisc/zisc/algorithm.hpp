/*!
  \file algorithm.hpp
  \author takemura
  */

#ifndef _ZISC_ALGORITHM_HPP_
#define _ZISC_ALGORITHM_HPP_

// Standard C++ library
#include <cstdint>

namespace zisc {

// Return the index of the container
template <class ForwardIterator, class Type>
std::size_t getIndex(ForwardIterator begin, ForwardIterator end, const Type& value);

// Return the index of the container
template <class ForwardIterator, class Type, class Function>
std::size_t getIndex(ForwardIterator begin, ForwardIterator end, 
                     const Type& value, Function compare);

//! Calculate the 32bit hash of string using FNV-1a
constexpr std::uint32_t toHash32(const char* string);

//! Calculate the 64bit hash of string using FNV-1a
constexpr std::uint64_t toHash64(const char* string);

} // namespace zisc

#include "algorithm-inl.hpp"

#endif // _ZISC_ALGORITHM_HPP_
