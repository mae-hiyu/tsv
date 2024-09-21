/*!
  \file tonemapping_method.hpp
  \author takemura
  */

#ifndef _REFLECT_TONEMAPPING_METHOD_HPP_
#define _REFLECT_TONEMAPPING_METHOD_HPP_

// Standard C++ library
#include <cstddef>
// Zisc
#include "zisc/matrix.hpp"
// Reflect
#include "LinearAlgebra/transformation.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QImage;
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class HdrImage;
class RendererSystem;

//! \addtogroup Tonemapping
//! \{

/*!
  \brief The interface of tonemapping class.
  \details
  No detailed.
  */
class TonemappingMethod
{
 public:
  //! Create tonemapping method
  TonemappingMethod(const QSettings& settings, const QString& prefix);

  virtual ~TonemappingMethod();


  //! Return the inverse gamma
  double inverseGamma() const;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Apply tonemapping
  virtual void tonemap(RendererSystem& system,
                       const HdrImage& hdr_image, 
                       QImage& ldr_image) const = 0;

  //! Return the xyz to rgb matrix
  const Matrix3x3& toRgbMatrix() const;

  //! Return the rgb to xyz matrix
  const Matrix3x3& toXyzMatrix() const;

 private:
  //! Initialize
  void initialize(const QSettings& settings, const QString& prefix);


  double inverse_gamma_;
  Matrix3x3 to_rgb_matrix_;
  Matrix3x3 to_xyz_matrix_;
};

//! Make tonemapping method
UniquePointer<TonemappingMethod> makeTonemappingMethod(const QSettings& settings,
                                                       const QString& prefix);

//! \} Tonemapping

} // namespace reflect

#include "tonemapping_method-inl.hpp"

#endif // _REFLECT_TONEMAPPING_METHOD_HPP_
