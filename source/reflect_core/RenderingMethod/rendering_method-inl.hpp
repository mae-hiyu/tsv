/*!
  \file rendering_method-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERING_METHOD_INL_HPP_
#define _REFLECT_RENDERING_METHOD_INL_HPP_

#include "rendering_method.hpp"
// Standard C++ library
#include <cstddef>
#include <functional>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "path_tracing.hpp"
#include "probabilistic_ppm.hpp"
#include "tsv.hpp"
#include "tsv-probabilistic_ppm.hpp"
#include "tsv-light.hpp"
#include "Sampling/russian_roulette.hpp"
#include "Sampling/sampled_wavelengths.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/value.hpp"

namespace reflect {

// Forward declaration
class ColorSystem;
class RendererSystem;
template <std::size_t> class SampledSpectra;
class Scene;

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
RenderingMethod<kSampleSize>::RenderingMethod(RendererSystem& system,
                                              const ColorSystem& color_system,
                                              const QSettings& settings, 
                                              Scene* scene) :
    scene_{scene}
{
  initialize(system, color_system, settings);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void RenderingMethod<kSampleSize>::operator()(RendererSystem& system)
{
  render(system);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
double RenderingMethod<kSampleSize>::rayCastEpsilon() const
{
  return ray_cast_epsilon_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
RouletteResult RenderingMethod<kSampleSize>::playRussianRoulette(
    const std::size_t path,
    const Spectra& weight,
    Sampler& sampler) const
{
  return russian_roulette_(path, weight, sampler);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
auto RenderingMethod<kSampleSize>::sampleWavelengths(Sampler& sampler) const
    -> Samples
{
  return sample_wavelengths_(sampler);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
Scene& RenderingMethod<kSampleSize>::sceneData()
{
  return *scene_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
const Scene& RenderingMethod<kSampleSize>::sceneData() const
{
  return *scene_;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
void RenderingMethod<kSampleSize>::initialize(RendererSystem& /* system */,
                                              const ColorSystem& color_system,
                                              const QSettings& settings)
{
  const auto& world = sceneData().world();

  // Wavelength sampler
  auto key = QString{keyword::color_group} + "/" + keyword::spectrum_sampling;
  const auto method = value<QString>(settings, key);
  sample_wavelengths_ = makeWavelengthSampler<kSampleSize>(color_system, 
                                                           method, 
                                                           world);

  // Russian rolette
  key = QString{keyword::rendering_method} + "/" + keyword::russian_roulette;
  russian_roulette_ = makeRussianRoulette<kSampleSize>(settings, key);

  // Ray cast epsilon
  key = QString{keyword::rendering_method} + "/" + keyword::ray_cast_epsilon;
  ray_cast_epsilon_ = value<double>(settings, key);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
UniquePointer<RenderingMethod<kSampleSize>> makeRenderingMethod(
    RendererSystem& system,
    const ColorSystem& color_system,
    const QSettings& settings,
    Scene* scene)
{
  RenderingMethod<kSampleSize>* method = nullptr;

  const auto key = QString{keyword::rendering_method_group} + "/" + 
                   keyword::rendering_method;
  const auto method_type = value<QString>(settings, key);
  switch (zisc::toHash32(method_type.toStdString().c_str())) {
   case zisc::toHash32(keyword::path_tracing_method):
    method = new PathTracing<kSampleSize>{system, color_system, settings, scene};
    break;
   case zisc::toHash32(keyword::probabilistic_ppm_method):
    method = new ProbabilisticPpm<kSampleSize, false>{system, color_system, 
                                                      settings, scene};
    break;
   case zisc::toHash32(keyword::tsv_probabilistic_ppm_method):
    method = new TSVProbabilisticPpm<kSampleSize, false>{system, color_system, 
                                                      settings, scene};
    break;
   case zisc::toHash32(keyword::tsv_rendering_method):
    method = new TSVPathTracing<kSampleSize>{system, color_system, settings, scene};
    break;
   case zisc::toHash32(keyword::tsv_light_rendering_method):
    method = new TSVLightPathTracing<kSampleSize>{system, color_system, settings, scene};
    break;
   default:
    zisc::raiseError("RenderingMethodError: Unsupported type is speficied.");
    break;
  }
  return UniquePointer<RenderingMethod<kSampleSize>>{method};
}

} // namespace reflect

#endif // _REFLECT_RENDERING_METHOD_INL_HPP_
