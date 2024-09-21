/*!
  \file cl_renderer.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_RENDERER_HPP_
#define _REFLECT_CL_RENDERER_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "cl.hpp"
#include "cl_core.hpp"
#include "RendererBase/renderer_base.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QImage;
class QSettings;

namespace reflect {

// Forward declaration
class ClScene;
class ClRenderingMethod;
class HdrImage;

//! \addtogroup OpenCL
//! \{

/*!
  \details
  No detailed.
  */
class ClRenderer : public RendererBase
{
 public:
  //! Create a renderer
  ClRenderer(const QSettings& settings);

  //! Release memory
  ~ClRenderer();


  //! Initialize renderer
  void initialize(const QSettings& settings) override;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Renderer scene
  void render() override;

 private:
  //! Save image
  void saveImage(const std::size_t pass);


  ClCore core_;
  UniquePointer<ClScene> scene_;
  UniquePointer<ClRenderingMethod> rendering_method_;
  UniquePointer<QImage> ldr_image_;
  UniquePointer<HdrImage> hdr_image_;
  std::size_t saving_interval_;
  std::size_t termination_pass_;
  bool saving_image_at_power_of_2_of_pass_;
};

//! \} OpenCL

} // namespace reflect

#endif // _REFLECT_CL_RENDERER_HPP_
