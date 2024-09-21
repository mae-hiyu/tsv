/*!
  \file non_directional_emitter.hpp
  \author takemura
  */

#ifndef _REFLECT_NON_DIRECTIONAL_EMITTER_HPP_
#define _REFLECT_NON_DIRECTIONAL_EMITTER_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "emitter_model.hpp"
#include "reflect_config.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
class IntersectionInfo;
class Sampler;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
class NonDirectionalEmitter : public EmitterModel
{
 public:
  //! Create a non directional emitter
  NonDirectionalEmitter(const ColorSystem& color_system,
                        const QSettings& settings, 
                        const QString& prefix);


  //! Make non-directional light
  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeNonDirectionalLight(
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the non-directional emitter type
  EmitterType type() const override;
};

//! \} Material

} // namespace reflect

#include "non_directional_emitter-inl.hpp"

#endif // _REFLECT_NON_DIRECTIONAL_EMITTER_HPP_
