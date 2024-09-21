/*!
 \file film-inl.hpp
 \author takemura
 */

#ifndef _REFLECT_FILM_INL_HPP_
#define _REFLECT_FILM_INL_HPP_

#include "film.hpp"
// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "Color/spectra_image_interface.hpp"
#include "LinearAlgebra/point.hpp"
#include "LinearAlgebra/vector.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
inline
double Film::aspectRatio() const
{
  return cast<double>(width_) * inverse_height_;
}

/*!
 \details
 No detailed.
 */
inline
Point2 Film::coordinate(const std::size_t x,
                        const std::size_t y, 
                        const Vector2& jittering) const 
{
  return Point2{(cast<double>(x) + jittering[0]) * inverse_width_,
                (cast<double>(y) + jittering[1]) * inverse_height_};
}

/*!
 \details
 No detailed.
 */
inline
std::size_t Film::heightResolution() const
{
  return height_;
}

/*!
  \details
  No detailed.
  */
inline
double Film::inverseAspectRatio() const
{
  return cast<double>(height_) * inverse_width_;
}

/*!
  \details
  No detailed.
  */
inline
bool Film::isEnabledJittering() const
{
  return jittering_;
}

/*!
 \details
 No detailed.
 */
inline
SpectraImageInterface& Film::spectraBuffer()
{
  return *spectra_buffer_;
}

/*!
 \details
 No detailed.
 */
inline
const SpectraImageInterface& Film::spectraBuffer() const
{
  return *spectra_buffer_;
}

/*!
 \details
 No detailed.
 */
inline
std::size_t Film::widthResolution() const
{
  return width_;
}

} // namespace reflect

#endif // _REFLECT_FILM_INL_HPP_
