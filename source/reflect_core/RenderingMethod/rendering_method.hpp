/*!
  \file rendering_method.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERING_METHOD_HPP_
#define _REFLECT_RENDERING_METHOD_HPP_

// Standard C++ library
#include <cstddef>
#include <functional>
// Reflect
#include "reflect_config.hpp"
#include "Utility/unique_pointer.hpp"
#include "Sampling/russian_roulette.hpp"
#include "Sampling/sampled_wavelengths.hpp"

// Forward declaration
class QSettings;

namespace reflect {

// Forward declaration
class ColorSystem;
class RendererSystem;
template <std::size_t> class SampledSpectra;
class Sampler;
class Scene;

//! \addtogroup RenderingMethod
//! \{

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class RenderingMethod
{
 public:
  using Spectra = SampledSpectra<kSampleSize>;
  using Samples = SampledWavelengths<kSampleSize>;
  using SamplesLight = SampledWavelengths<kLightSampleSize>;
  using SamplesXYZ = SampledWavelengths<kXYZSampleSize>;


  //! Create a rendering method
  RenderingMethod(RendererSystem& system,
                  const ColorSystem& color_system,
                  const QSettings& settings, 
                  Scene* scene);

  virtual ~RenderingMethod() {}


  //! Render scene
  void operator()(RendererSystem& system);


  //! Return the ray cast epsilon
  double rayCastEpsilon() const;

  //! Render scene
  virtual void render(RendererSystem& system) = 0;

 protected:
  //! Play russian roulette
  RouletteResult playRussianRoulette(const std::size_t path,
                                     const Spectra& weight,
                                     Sampler& sampler) const;

  //! Sample wavelengths
  Samples sampleWavelengths(Sampler& sampler) const;

  //! Return the scene
  Scene& sceneData();

  //! Return the scene
  const Scene& sceneData() const;

 private:
  //! Initialize
  void initialize(RendererSystem& system,
                  const ColorSystem& color_system,
                  const QSettings& settings);


  Scene* scene_;
  std::function<Samples (Sampler&)> sample_wavelengths_;
  RussianRouletteFunction<kSampleSize> russian_roulette_;
  double ray_cast_epsilon_;
};

//! Make rendering method
template <std::size_t kSampleSize>
UniquePointer<RenderingMethod<kSampleSize>> makeRenderingMethod(
    RendererSystem& system,
    const ColorSystem& color_system,
    const QSettings& settings,
    Scene* scene);

//! \} RenderingMethod

} // namespace reflect

#include "rendering_method-inl.hpp"

#endif // _REFLECT_RENDERING_METHOD_HPP_
