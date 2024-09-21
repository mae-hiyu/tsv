/*!
  \file arithmetic_array-inl.hpp
  \author takemura
  */

#ifndef _ZISC_ARITHMETIC_ARRAY_INL_HPP_
#define _ZISC_ARITHMETIC_ARRAY_INL_HPP_

#include "arithmetic_array.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "math.hpp"
#include "utility.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN>::ArithmeticArray()
{
  fill(cast<Arithmetic>(0));
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> template <typename ...Types> inline
ArithmeticArray<Arithmetic, kN>::ArithmeticArray(const Types ...values)
{
  fill(cast<Arithmetic>(0));
  setElements(values...);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN>::ArithmeticArray(const ArithmeticArray& array)
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] = array.elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator+(const ArithmeticArray& other) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = elements_[index] + other.elements_[index];
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator-(const ArithmeticArray& other) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = elements_[index] - other.elements_[index];
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator*(const Arithmetic scalar) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = elements_[index] * scalar;
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator*(const ArithmeticArray& other) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = elements_[index] * other.elements_[index];
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator/(const Arithmetic scalar) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = elements_[index] / scalar;
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator/(const ArithmeticArray& other) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = elements_[index] / other.elements_[index];
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator+=(const ArithmeticArray& other)
    -> ArithmeticArray&
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] += other.elements_[index];
  return *this;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator-=(const ArithmeticArray& other)
    -> ArithmeticArray&
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] -= other.elements_[index];
  return *this;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator*=(const Arithmetic scalar)
    -> ArithmeticArray&
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] *= scalar;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator*=(const ArithmeticArray& other)
    -> ArithmeticArray&
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] *= other.elements_[index];
  return *this;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator/=(const Arithmetic scalar)
    -> ArithmeticArray&
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] /= scalar;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::operator/=(const ArithmeticArray& other)
    -> ArithmeticArray&
{
  for (std::size_t index = 0; index < kN; ++index)
    elements_[index] /= other.elements_[index];
  return *this;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic& ArithmeticArray<Arithmetic, kN>::operator[](const std::size_t index)
{
  return elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
const Arithmetic& ArithmeticArray<Arithmetic, kN>::operator[](const std::size_t index) const
{
  return elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
void ArithmeticArray<Arithmetic, kN>::clamp(const Arithmetic min,
                                            const Arithmetic max)
{
  for (auto& element : elements_)
    element = zisc::clamp(min, max, element);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::divideScalar(const Arithmetic scalar) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = scalar / elements_[index];
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN>
void ArithmeticArray<Arithmetic, kN>::fill(const Arithmetic value)
{
  for (auto& element : elements_)
    element = value;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic ArithmeticArray<Arithmetic, kN>::get(const std::size_t index) const
{
  return elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
bool ArithmeticArray<Arithmetic, kN>::isZero() const
{
  for (const auto value : elements_) {
    if (value != cast<Arithmetic>(0))
      return false;
  }
  return true;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic ArithmeticArray<Arithmetic, kN>::max() const
{
  Arithmetic max = elements_[0];
  for (std::size_t index = 1; index < kN; ++index)
    max = zisc::max(elements_[index], max);
  return max;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic ArithmeticArray<Arithmetic, kN>::min() const
{
  Arithmetic min = elements_[0];
  for (std::size_t index = 1; index < kN; ++index)
    min = zisc::min(elements_[index], min);
  return min;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::maxElements(const ArithmeticArray& other) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = zisc::max(other.elements_[index], elements_[index]);
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
auto ArithmeticArray<Arithmetic, kN>::minElements(const ArithmeticArray& other) const 
    -> ArithmeticArray
{
  ArithmeticArray array{this};
  for (std::size_t index = 0; index < kN; ++index)
    array.elements_[index] = zisc::min(other.elements_[index], elements_[index]);
  return array;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
void ArithmeticArray<Arithmetic, kN>::set(const std::size_t index, 
                                          const Arithmetic value)
{
  elements_[index] = value;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> template <typename ...Types> inline
void ArithmeticArray<Arithmetic, kN>::setElements(const Types ...values)
{
  static_assert(sizeof...(Types) <= kN, "The number of parameters is wrong.");
  setElements<0>(cast<Arithmetic>(values)...);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN>::ArithmeticArray(const ArithmeticArray* /* array */)
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> 
template <std::size_t index, typename ...Types> inline
void ArithmeticArray<Arithmetic, kN>::setElements(const Arithmetic value, 
                                                  const Types ...values)
{
  setElements<index>(value);
  setElements<index + 1>(values...);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> template <std::size_t index> inline
void ArithmeticArray<Arithmetic, kN>::setElements(const Arithmetic value)
{
  elements_[index] = value;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic ArithmeticArray<Arithmetic, kN>::sum() const
{
  Arithmetic sum = elements_[0];
  for (std::size_t index = 1; index < kN; ++index)
    sum += elements_[index];
  return sum;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
bool operator==(const ArithmeticArray<Arithmetic, kN>& a, 
                const ArithmeticArray<Arithmetic, kN>& b)
{
  for (std::size_t index = 0; index < kN; ++index) {
    if (a[index] != b[index])
      return false;
  }
  return true;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
bool operator!=(const ArithmeticArray<Arithmetic, kN>& a, 
                const ArithmeticArray<Arithmetic, kN>& b)
{
  return !(a == b);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN> operator*(
    const Arithmetic scalar,
    const ArithmeticArray<Arithmetic, kN>& array)
{
  return array * scalar;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN> operator/(
    const Arithmetic scalar,
    const ArithmeticArray<Arithmetic, kN>& array)
{
  return array.divideScalar(scalar);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic> inline
ArithmeticArray<Arithmetic, 3>  cross(const ArithmeticArray<Arithmetic, 3>& a, 
                                      const ArithmeticArray<Arithmetic, 3>& b)
{
  return ArithmeticArray<Arithmetic, 3>{a[1] * b[2] - a[2] * b[1],
                                        a[2] * b[0] - a[0] * b[2],
                                        a[0] * b[1] - a[1] * b[0]};
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic dot(const ArithmeticArray<Arithmetic, kN>& a, 
               const ArithmeticArray<Arithmetic, kN>& b)
{
  Arithmetic dot = a[0] * b[0];
  for (std::size_t index = 1; index < kN; ++index)
    dot += a[index] * b[index];
  return dot;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN> maxElements(
    const ArithmeticArray<Arithmetic, kN>& a,
    const ArithmeticArray<Arithmetic, kN>& b)
{
  return a.maxElements(b);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
ArithmeticArray<Arithmetic, kN> minElements(
    const ArithmeticArray<Arithmetic, kN>& a,
    const ArithmeticArray<Arithmetic, kN>& b)
{
  return a.minElements(b);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
void minMaxElements(ArithmeticArray<Arithmetic, kN>& a,
                    ArithmeticArray<Arithmetic, kN>& b)
{
  for (std::size_t i = 0; i < kN; ++i) {
    if (b[i] < a[i]) {
      const Arithmetic t = a[i];
      a[i] = b[i];
      b[i] = t;
    }
  }
}

} // namespace zisc

#endif // _ZISC_ARITHMETIC_ARRAY_INL_HPP_
