/*!
  \file algorithm-inl.hpp
  \author takemura
  */

#ifndef _ZISC_ALGORITHM_INL_HPP_
#define _ZISC_ALGORITHM_INL_HPP_

#include "algorithm.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>
// Zisc
#include "utility.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <class ForwardIterator, class Type> inline
std::size_t getIndex(ForwardIterator begin, ForwardIterator end, const Type& value)
{
  auto position = std::lower_bound(begin, end, value);
  return std::distance(begin, position);
}

/*!
  \details
  No detailed.
  */
template <class ForwardIterator, class Type, class Function> inline
std::size_t getIndex(ForwardIterator begin, ForwardIterator end,
                     const Type& value, Function compare)
{
  auto position = std::lower_bound(begin, end, value, compare);
  return std::distance(begin, position);
}

namespace inner {

/*!
  \brief Calculate the hash of string using FNV-1a
  \details
  Please see the details of this algorithm below URL
  http://www.isthe.com/chongo/tech/comp/fnv/
  */
template <typename ValueType, ValueType kPrime> inline
constexpr ValueType toHash(const char* string, const ValueType hash)
{
  return (*string != '\0') 
      ? toHash<ValueType, kPrime>(string + 1, 
                                  (hash ^ cast<ValueType>(*string)) * kPrime)
      : hash;
}

} // namespace inner  

/*!
  \details
  No detailed.
  */
constexpr std::uint32_t toHash32(const char* string)
{
  // The FNV offset basis is 2166136261
  // The FNV prime is 16777619
  return inner::toHash<std::uint32_t, 16777619>(string, 2166136261);
}

/*!
  \details
  No detailed.
  */
constexpr std::uint64_t toHash64(const char* string)
{
  // The FNV offset basis is 14695981039346656037
  // The FNV prime is 1099511628211
  return inner::toHash<std::uint64_t, 1099511628211>(
      string, 14695981039346656037ull);
}

} // namespace zisc

#endif // _ZISC_ALGORITHM_INL_HPP_
