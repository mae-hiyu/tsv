/*!
  \file reinhard.hpp
  \author takemura
  */

#ifndef _REFLECT_REINHARD_HPP_
#define _REFLECT_REINHARD_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "tonemapping_method.hpp"

// Forward declaration
class QImage;
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class HdrImage;
class RendererSystem;

/*!
  \details
  No detailed.
  */
class Reinhard : public TonemappingMethod
{
 public:
  //! Create Reinhard tonemapping
  Reinhard(const QSettings& settings, const QString& prefix);;


  void setKey(const double key_value);

  //! Apply tonemapping
  void tonemap(RendererSystem& system,
               const HdrImage& hdr_image, 
               QImage& ldr_image) const override;

 private:
  double key_;
};

} // namespace reflect

#endif // _REFLECT_REINHARD_HPP_
