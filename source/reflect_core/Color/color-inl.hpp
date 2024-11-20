/*!
  \file color-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_INL_HPP_
#define _REFLECT_COLOR_INL_HPP_

#include "color.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/type_traits.hpp"
#include "zisc/utility.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
Color<kN>::Color()
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> template <typename ...Types> inline
Color<kN>::Color(const Types ...elements) :
    color_{elements...}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
Color<kN>::Color(const zisc::ArithmeticArray<double, kN>& color) :
    color_{color}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
double& Color<kN>::operator[](const std::size_t index)
{
  return color_[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
const double& Color<kN>::operator[](const std::size_t index) const
{
  return color_[index];
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
void Color<kN>::clamp()
{
  for (std::size_t index = 0; index < kN; ++index)
    color_[index] = zisc::clamp(0.0, 1.0, color_[index]);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
const zisc::ArithmeticArray<double, kN>& Color<kN>::data() const
{
  return color_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
bool Color<kN>::isZero() const
{
  return color_.isZero();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
double Color<kN>::max() const
{
  return color_.max();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN> inline
void Color<kN>::scale()
{
  const double scale_factor = 1.0 / max();
  color_ = color_ * scale_factor;
}

/*!
  \details
  No detailed.
  */
template <typename Type, zisc::EnableIfBaseOf<Color<3>, Type>> inline
Type operator*(const Type& color, const double scalar)
{
  return Type{color.data() * scalar};
}

/*!
  \detailsddsfsad
  No detailed.
  */
template <typename Type, zisc::EnableIfBaseOf<Color<3>, Type>> inline
Type operator*(const double scalar, const Type& color)
{
  return color * scalar;
}

} // namespace reflect

#endif // _REFLECT_COLOR_INL_HPP_
