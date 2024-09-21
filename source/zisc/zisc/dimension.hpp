/*!
  \file dimension.hpp
  \author takemura
  */

#ifndef _ZISC_DIMENSION_HPP_
#define _ZISC_DIMENSION_HPP_

// Standard C++ library
#include <cstddef>
#include <type_traits>
// Zisc
#include "arithmetic_array.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN>
class Dimension
{
 public:
  using ArrayType = ArithmeticArray<Arithmetic, kN>;
  using ValueType = Arithmetic;


  //! Initialize with 0
  Dimension();

  //! Initialize with values
  template <typename ...Types>
  Dimension(const Types ...values);

  //! Initialize with array
  Dimension(const ArrayType& array);


  //! Get the reference by index.
  Arithmetic& operator[](const std::size_t index);

  //! Get the reference by index.
  const Arithmetic& operator[](const std::size_t index) const;

  //! Get array reference
  ArrayType& data();

  //! Get array reference
  const ArrayType& data() const;

  //! Get an element by index.
  Arithmetic get(const std::size_t index) const;

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

 private:
  ArrayType elements_;
};

} // namespace zisc

#include "dimension-inl.hpp"

#endif // _ZISC_DIMENSION_HPP_
