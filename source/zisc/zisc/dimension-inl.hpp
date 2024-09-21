/*!
  \file dimension-inl.hpp
  \author takemura
  */

#ifndef _ZISC_DIMENSION_INL_HPP_
#define _ZISC_DIMENSION_INL_HPP_

#include "dimension.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "arithmetic_array.hpp"
#include "math.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
Dimension<Arithmetic, kSize>::Dimension()
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> template <typename ...Types> inline
Dimension<Arithmetic, kSize>::Dimension(const Types ...values) :
    elements_{values...}
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
Dimension<Arithmetic, kSize>::Dimension(const ArrayType& array) :
    elements_{array}
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
Arithmetic& Dimension<Arithmetic, kSize>::operator[](const std::size_t index)
{
  return elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
const Arithmetic& Dimension<Arithmetic, kSize>::operator[](
    const std::size_t index) const
{
  return elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
auto Dimension<Arithmetic, kSize>::data() -> ArrayType&
{
  return elements_;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
auto Dimension<Arithmetic, kSize>::data() const -> const ArrayType&
{
  return elements_;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
Arithmetic Dimension<Arithmetic, kSize>::get(const std::size_t index) const
{
  return elements_[index];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> inline
void Dimension<Arithmetic, kSize>::set(const std::size_t index, 
                                       const Arithmetic value)
{
  elements_.set(index, value);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kSize> template <typename ...Types> inline
void Dimension<Arithmetic, kSize>::setElements(const Types ...values)
{
  elements_.setElements(values...);
}

} // namespace zisc

#endif // _ZISC_DIMENSION_INL_HPP_
