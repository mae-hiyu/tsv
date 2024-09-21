/*!
  \file emitter_model.hpp
  \author takemura
  */

#ifndef _REFLECT_EMITTER_MODEL_HPP_
#define _REFLECT_EMITTER_MODEL_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Color/spectral_distribution.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class ColorSystem;
class IntersectionInfo;
class Sampler;
template <std::size_t> class ShaderModel;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
enum class EmitterType : int
{
  NonDirectional = 0,
};

/*!
  \details
  No detailed.
  */
class EmitterModel
{
 public:
  template <std::size_t kSampleSize>
  using ShaderPointer = UniquePointer<ShaderModel<kSampleSize>>;


  //! Create a emitter model
  EmitterModel(const ColorSystem& color_system,
               const QSettings& settings, 
               const QString& prefix);

  virtual ~EmitterModel() {};


  template <std::size_t kSampleSize>
  ShaderPointer<kSampleSize> makeLight(
      const IntersectionInfo& intersection,
      const WavelengthSamples<kSampleSize>& wavelengths,
      Sampler& sampler,
      MemoryPool& memory_pool) const;

  //! Return the spectral power distribution
  const SpectralDistribution& powerDistribution() const;

  //! Return the radiant emittance
  double radiantEmittance() const;

  //! Return the emitter type
  virtual EmitterType type() const = 0;
 
 protected:
  //! Scale the intensity of property
  void scale(const double scale);

 private:
  //! Initialize
  void initialize(const ColorSystem& color_system,
                  const QSettings& settings, 
                  const QString& prefix);


  double radiant_emittance_;
  SpectralDistribution power_distribution_;
};

//! Make a non directional emitter
template <std::size_t kSampleSize>
EmitterModel::ShaderPointer<kSampleSize> makeNonDirectionalLight(
    const EmitterModel* emitter,
    const IntersectionInfo& intersection,
    const WavelengthSamples<kSampleSize>& wavelengths,
    Sampler& sampler,
    MemoryPool& memory_pool);

//! Make a emitter model
UniquePointer<EmitterModel> makeEmitter(const ColorSystem& color_system,
                                        const QSettings& settings,
                                        const QString& prefix);

//! \} Material

} // namespace reflect

#include "emitter_model-inl.hpp"

#endif // _REFLECT_EMITTER_MODEL_HPP_
