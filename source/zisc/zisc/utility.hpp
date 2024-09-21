/*!
  \file utility.hpp
  \author takemura
  */

#ifndef _ZISC_UTILITY_HPP_
#define _ZISC_UTILITY_HPP_

// Standard C++ library
#include <type_traits>

namespace zisc {

//! Convert type from T to Type
template <typename Type, typename T>
constexpr Type cast(const T value);

//! Clamp the value
template <typename Arithmetic>
constexpr Arithmetic clamp(const Arithmetic min, 
                           const Arithmetic max, 
                           const Arithmetic x);

//! Get the sign bit (MSB)
template <typename SignedInteger>
constexpr SignedInteger getSignedBit();

//! Treat T* as Type*
template <typename Type, typename T>
constexpr Type treatAs(const T* object);

//! Treat T* as Type*
template <typename Type, typename T>
constexpr Type treatAs(T* object);

} // namespace zisc

#include "utility-inl.hpp"

#endif // _ZISC_UTILITY_HPP_
