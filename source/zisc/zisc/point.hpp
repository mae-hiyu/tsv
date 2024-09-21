/*!
  \file point.hpp
  \author takemura
  */

#ifndef _ZISC_POINT_HPP_
#define _ZISC_POINT_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "arithmetic_array.hpp"
#include "dimension.hpp"
#include "vector.hpp"

namespace zisc {

/*!
  \brief N dimension point
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN>
class Point : public Dimension<Arithmetic, kN>
{
 public:
  using ArrayType = ArithmeticArray<Arithmetic, kN>;


  //! Initialize with 0
  Point();

  //! Initialize with values
  template <typename ...Types>
  Point(const Types ...values);

  //! Initialize with array
  Point(const ArrayType& array);
};

template <typename Arithmetic, std::size_t kN>
Vector<Arithmetic, kN> operator-(const Point<Arithmetic, kN>& a,
                                 const Point<Arithmetic, kN>& b);

template <typename Arithmetic, std::size_t kN>
Point<Arithmetic, kN> operator+(const Point<Arithmetic, kN>& point,
                                const Vector<Arithmetic, kN>& vector);

template <typename Arithmetic, std::size_t kN>
Point<Arithmetic, kN> operator+(const Vector<Arithmetic, kN>& vector,
                                const Point<Arithmetic, kN>& point);

template <typename Arithmetic, std::size_t kN>
Point<Arithmetic, kN> operator-(const Point<Arithmetic, kN>& point,
                                const Vector<Arithmetic, kN>& vector);

} // namespace zisc

#include "point-inl.hpp"

#endif // _ZISC_POINT_HPP_
