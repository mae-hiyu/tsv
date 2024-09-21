/*!
 \file renderer.hpp
 \author takemura
 */

#ifndef _REFLECT_RENDERER_HPP_
#define _REFLECT_RENDERER_HPP_

// Standard C++ library
#include <cstdint>
// Reflect
#include "RendererBase/renderer_base.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QImage;
class QSettings;
class QTextStream;

namespace reflect {

// Forward declaration
class HdrImage;
template <std::size_t> class RenderingMethod;
class Scene;

/*!
  \details
  No detailed.
  */
class Renderer : public RendererBase
{
 public:
  using Method = RenderingMethod<kWavelengthSampleSize>;


  //! Create a renderer
  Renderer(const QSettings& settings);

  //! Release memory
  ~Renderer();


  //! Initialize renderer
  void initialize(const QSettings& settings) override;

  //! Render scene
  void render() override;

 private:
  //! Output finish message
  void outputPassFinishMessage(const std::size_t pass,
                               const std::int64_t pass_time,
                               const std::int64_t total_time) const;

  //! Output pass start message
  void outputPassStartMessage(const std::size_t pass) const;

  //! Save image
  void saveImage(const std::size_t pass);


  bool enable_spectra_image_saving_;
  bool enable_hdr_image_saving_;
  bool saving_image_at_power_of_2_of_pass_;
  std::size_t termination_pass_;
  std::int64_t saving_interval_;
  UniquePointer<Scene> scene_;
  UniquePointer<QImage> ldr_image_;
  UniquePointer<HdrImage> hdr_image_;
  UniquePointer<Method> rendering_method_;
};

} // namespace reflect

#endif // _REFLECT_RENDERER_HPP_
