/*!
  \file point-inl.hpp
  \author takemura
  */

#ifndef _ZISC_POINT_INL_HPP_
#define _ZISC_POINT_INL_HPP_

#include "point.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "arithmetic_array.hpp"
#include "dimension.hpp"
#include "vector.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Point<Arithmetic, kN>::Point()
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> template <typename ...Types> inline
Point<Arithmetic, kN>::Point(const Types ...values) :
    Dimension<Arithmetic, kN>(values...)
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Point<Arithmetic, kN>::Point(const ArrayType& array) :
    Dimension<Arithmetic, kN>(array)
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Vector<Arithmetic, kN> operator-(const Point<Arithmetic, kN>& a,
                                 const Point<Arithmetic, kN>& b)
{
  return Vector<Arithmetic, kN>{a.data() - b.data()};
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Point<Arithmetic, kN> operator+(const Point<Arithmetic, kN>& point,
                                const Vector<Arithmetic, kN>& vector)
{
  return Point<Arithmetic, kN>{point.data() + vector.data()};
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Point<Arithmetic, kN> operator+(const Vector<Arithmetic, kN>& vector,
                                const Point<Arithmetic, kN>& point)
{
  return point + vector;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Point<Arithmetic, kN> operator-(const Point<Arithmetic, kN>& point,
                                const Vector<Arithmetic, kN>& vector)
{
  return Point<Arithmetic, kN>{point.data() - vector.data()};
}

} // namespace zisc

#endif // _ZISC_POINT_INL_HPP_
