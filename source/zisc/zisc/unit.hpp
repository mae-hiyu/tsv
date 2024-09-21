/*!
  \file unit.hpp
  \author takemura
  */

#ifndef _ZISC_UNIT_HPP_
#define _ZISC_UNIT_HPP_

namespace zisc {

//! Convert degree to radian
template <typename Float>
constexpr Float toRadian(const Float angle);

//! Convert radian to degree
template <typename Float>
constexpr Float toAngle(const Float radian);

} // namespace zisc

#include "unit-inl.hpp"

#endif // _ZISC_UNIT_HPP_
