/*!
  \file arithmetic_array.hpp
  \author takemura
  */

#ifndef _ZISC_ARITHMETIC_ARRAY_HPP_
#define _ZISC_ARITHMETIC_ARRAY_HPP_

// Standard C++ library
#include <cstddef>

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN>
class ArithmeticArray
{
 public:
  using ValueType = Arithmetic;


  //! Initialize with 0
  ArithmeticArray();

  //! Initialize with values
  template <typename ...Types>
  ArithmeticArray(const Types ...values);

  //! Initialize with array
  ArithmeticArray(const ArithmeticArray& array);


  //! Apply addition operation to each element in the array
  ArithmeticArray operator+(const ArithmeticArray& other) const;

  //! Apply subtraction operation to each element in the array
  ArithmeticArray operator-(const ArithmeticArray& other) const;

  //! Multiply each element by a scalar
  ArithmeticArray operator*(const Arithmetic scalar) const;

  //! Apply multiplication operation to each element in the array
  ArithmeticArray operator*(const ArithmeticArray& other) const;

  //! Divide each element by a scalar
  ArithmeticArray operator/(const Arithmetic scalar) const;

  //! Apply division operation to each element in the array
  ArithmeticArray operator/(const ArithmeticArray& other) const;

  //!
  ArithmeticArray& operator+=(const ArithmeticArray& other);

  //!
  ArithmeticArray& operator-=(const ArithmeticArray& other);

  //!
  ArithmeticArray& operator*=(const Arithmetic scalar);

  //!
  ArithmeticArray& operator*=(const ArithmeticArray& other);

  //!
  ArithmeticArray& operator/=(const Arithmetic scalar);

  //!
  ArithmeticArray& operator/=(const ArithmeticArray& other);

  //! Get the reference by index
  Arithmetic& operator[](const std::size_t index);

  //! Get the reference by index
  const Arithmetic& operator[](const std::size_t index) const;


  //! Clamp all elements
  void clamp(const Arithmetic min, const Arithmetic max);

  //! Divide a scalar by a array
  ArithmeticArray divideScalar(const Arithmetic scalar) const;

  //! Fill the container with specified value
  void fill(const Arithmetic value);

  //! Get an element by index.
  Arithmetic get(const std::size_t index) const;

  //! Check whether all elements are zero
  bool isZero() const;

  //! Return the largest element
  Arithmetic max() const;

  //! Return the smallest element
  Arithmetic min() const;

  //! Compare two arrays and store maximum values
  ArithmeticArray maxElements(const ArithmeticArray& other) const;

  //! Compare two arrays and store minimum values
  ArithmeticArray minElements(const ArithmeticArray& other) const;

  //! Set value
  void set(const std::size_t index, const Arithmetic value);

  //! Set values
  template <typename ...Types>
  void setElements(const Types ...values);

  //! Return the number of elements
  static constexpr std::size_t size()
  {
    return kN;
  }

  //! Get sum of elements
  Arithmetic sum() const;

 private:
  //! Create a instance without initialization
  ArithmeticArray(const ArithmeticArray* array);


  //! Set value
  template <std::size_t index, typename ...Types>
  void setElements(const Arithmetic value, const Types ...values);

  //! Set value
  template <std::size_t index>
  void setElements(const Arithmetic value);


  Arithmetic elements_[kN];
};

//! Check whether two arrays are same
template <typename Arithmetic, std::size_t kN>
bool operator==(const ArithmeticArray<Arithmetic, kN>& a, 
                const ArithmeticArray<Arithmetic, kN>& b);

//! Check whether two arrays are not same
template <typename Arithmetic, std::size_t kN>
bool operator!=(const ArithmeticArray<Arithmetic, kN>& a, 
                const ArithmeticArray<Arithmetic, kN>& b);

//! Multiply each element by a scalar
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> operator*(
    const Arithmetic scalar,
    const ArithmeticArray<Arithmetic, kN>& array);

//! Divide a scalar by a array
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> operator/(
    const Arithmetic scalar,
    const ArithmeticArray<Arithmetic, kN>& array);
                                    
//! Calculate the cross product
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> cross(const ArithmeticArray<Arithmetic, kN>& a,
                                      const ArithmeticArray<Arithmetic, kN>& b);

//! Calculate the inner product
template <typename Arithmetic, std::size_t kN>
Arithmetic dot(const ArithmeticArray<Arithmetic, kN>& a, 
               const ArithmeticArray<Arithmetic, kN>& b);

//! Compare two arrays and store maximum values
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> maxElements(
    const ArithmeticArray<Arithmetic, kN>& a,
    const ArithmeticArray<Arithmetic, kN>& b);

//! Compare two arrays and store minimum values
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> minElements(
    const ArithmeticArray<Arithmetic, kN>& a,
    const ArithmeticArray<Arithmetic, kN>& b);

//! Compare two arrays and store minimu values to a and maximum values to b
template <typename Arithmetic, std::size_t kN>
void minMaxElements(ArithmeticArray<Arithmetic, kN>& a,
                    ArithmeticArray<Arithmetic, kN>& b);

} // namespace zisc

#include "arithmetic_array-inl.hpp"

#endif // _ZISC_ARITHMETIC_ARRAY_HPP_
