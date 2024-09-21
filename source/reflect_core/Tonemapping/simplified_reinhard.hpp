/*!
  \file simplified_reinhard.hpp
  \author takemura
  */

#ifndef _REFLECT_SIMPLIFIED_REINHARD_HPP_
#define _REFLECT_SIMPLIFIED_REINHARD_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "tonemapping_method.hpp"

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
  \details
  No detailed.
  */
class SimplifiedReinhard : public TonemappingMethod
{
 public:
  //! Initialize simplified reinhard
  SimplifiedReinhard(const QSettings& settings, const QString& prefix);


  //! Apply tonemapping
  void tonemap(RendererSystem& system,
               const HdrImage& hdr_image, 
               QImage& ldr_image) const override;
};

//! \} Tonemapping

} // namespace reflect

#endif // _REFLECT_SIMPLIFIED_REINHARD_HPP_
