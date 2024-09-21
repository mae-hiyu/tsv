/*!
 \file film.hpp
 \author takemura
 */

#ifndef _REFLECT_FILM_HPP_
#define _REFLECT_FILM_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Color/spectra_image_interface.hpp"
#include "LinearAlgebra/point.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
class Sampler;

//! \addtogroup CameraModel
//! \{

/*!
 \details
 No detailed.
 */
class Film
{
 public:
  //! Create film
  Film(const ColorSystem& color_system,
       const QSettings& settings, 
       const QString& prefix);


  //! Return the aspect ratio of image
  double aspectRatio() const;

  //! Sample film coordinate randomly
  Point2 coordinate(const std::size_t x, 
                    const std::size_t y,
                    const Vector2& jittering) const;

  //! Return image height
  std::size_t heightResolution() const;

  //! Return the inverse aspect ratio
  double inverseAspectRatio() const;

  //! Check if jittering is enabled
  bool isEnabledJittering() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return spectra pixel buffer
  SpectraImageInterface& spectraBuffer();

  //! Return spectra pixel buffer
  const SpectraImageInterface& spectraBuffer() const;

  //! Return image width resolution
  std::size_t widthResolution() const;

 private:
  //! Initialize
  void initialize(const ColorSystem& color_system,
                  const QSettings& settings,
                  const QString& prefix);


  UniquePointer<SpectraImageInterface> spectra_buffer_; //!< The buffer of spectra
  double inverse_width_,
         inverse_height_;
  std::size_t width_, //!< Image width resolution
              height_; //!< Image height resolution
  bool jittering_;
};

//! \} CameraModel

} // namespace reflect

#include "film-inl.hpp"

#endif // _REFLECT_FILM_HPP_
