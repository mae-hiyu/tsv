/*!
  \file color.hpp
  \author takemura
  */

#ifndef _REFLECT_COLOR_HPP_
#define _REFLECT_COLOR_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/type_traits.hpp"

namespace reflect {

//! \addtogroup Color
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kN>
class Color
{
 public:
  //! Creaet a color
  Color();

  //! Create a color
  template <typename ...Types>
  Color(const Types ...elements);

  //! Create a color
  Color(const zisc::ArithmeticArray<double, kN>& color);


  //! Return the element of the color by the index
  double& operator[](const std::size_t index);

  //! Return the element of the color by the index
  const double& operator[](const std::size_t index) const;


  //! Clamp the elements of the color to a range [0, 1]
  void clamp();

  //! Return the raw array
  const zisc::ArithmeticArray<double, kN>& data() const;

  //! Check whether all elements is zero
  bool isZero() const;

  //! Return the max value
  double max() const;

  //! All elements are scaled by using the inverse max value
  void scale();

 protected:
  zisc::ArithmeticArray<double, kN> color_;
};

//! Multiplay color and scalar
template <typename Type, zisc::EnableIfBaseOf<Color<3>, Type> = zisc::kEnabler>
Type operator*(const Type& color, const double scalar);

//! Multiplay color and scalar
template <typename Type, zisc::EnableIfBaseOf<Color<3>, Type> = zisc::kEnabler>
Type operator*(const double scalar, const Type& color);

//! \} Color

} // namespace reflect

#include "color-inl.hpp"

#endif // _REFLECT_COLOR_HPP_
