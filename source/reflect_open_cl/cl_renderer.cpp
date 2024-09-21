/*!
  \file cl_renderer.cpp
  \author takemura
  */

#include "cl_renderer.hpp"
// Standard C++ library
#include <cstdint>
#include <cstddef>
#include <vector>
#include <utility>
// Qt
#include <QFile>
#include <QImage>
#include <QSettings>
#include <QString>
#include <QTextStream>
// Zisc
#include "zisc/stopwatch.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "cl.hpp"
#include "cl_core.hpp"
#include "cl_scene.hpp"
#include "keyword.hpp"
#include "scene.hpp"
#include "Color/hdr_image.hpp"
#include "OpenCL/RenderingMethod/cl_rendering_method.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_manager.hpp"
#include "Utility/size.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ClRenderer::ClRenderer(const QSettings& settings) :
    RendererBase(settings),
    core_{settings}
{
}

/*!
  \details
  No detailed.
  */
ClRenderer::~ClRenderer()
{
}

/*!
  \details
  No detailed.
  */
void ClRenderer::initialize(const QSettings& settings)
{
  // Initialize scene
  Scene scene{settings, manager()};
  scene_ = new ClScene{scene.toClType()};
  std::size_t memory_size = scene_->initializeBuffer(core_);

  // Rendering method
  rendering_method_ = makeClRenderingMethod(settings, core_, *scene_);
  memory_size += rendering_method_->bufferMemorySize();

  // Output memory usage
  constexpr double to_megabyte = 1.0 / 1000000.0;
  const double memory_usage = cast<double>(memory_size) * to_megabyte;
  const auto message = QStringLiteral("OpenCL memory usage: %1 MB").arg(memory_usage);
  emit manager().outputText(message);

  // Image
  const auto& film = scene.film();
  ldr_image_ = new QImage{cast<int>(film.widthResolution()), 
                          cast<int>(film.heightResolution()), 
                          QImage::Format_RGB32};
  hdr_image_ = new HdrImage{film.widthResolution(), film.heightResolution()};

  auto key = QString{keyword::system_group} + "/" + 
             keyword::saving_image_at_power_of_2_of_pass;
  saving_image_at_power_of_2_of_pass_ = value<bool>(settings, key);

  key = QString{keyword::system_group} + "/" + keyword::saving_interval;
  saving_interval_ = value<std::int64_t>(settings, key);

  key = QString{keyword::system_group} + "/" + keyword::termination_pass;
  termination_pass_ = value<std::size_t>(settings, key);
}

/*!
  \details
  No detailed.
  */
std::size_t ClRenderer::printMemberData()
{
  std::size_t size = RendererBase::printMemberData();
  size += PRINT_VARIABLE_DATA(core_);
  size += PRINT_VARIABLE_DATA(scene_);
  size += PRINT_VARIABLE_DATA(rendering_method_);
  size += PRINT_VARIABLE_DATA(ldr_image_);
  size += PRINT_VARIABLE_DATA(hdr_image_);
  size += PRINT_VARIABLE_DATA(saving_interval_);
  size += PRINT_VARIABLE_DATA(termination_pass_);
  size += PRINT_VARIABLE_DATA(saving_image_at_power_of_2_of_pass_);
  return size;
}

/*!
  \details
  No detailed.
  */
void ClRenderer::render()
{
  bool is_image_saving_pass = false;
  std::size_t pass = 1;
  std::size_t saving_pass = 1;
  std::int64_t total_time = 0;

  zisc::Stopwatch timer;
  const auto& manager = RendererBase::manager();

  // Log data
  auto image_data_log = makeLogText("image_data.csv");
  image_data_log << "pass,    total time (ms)" << endl;

  timer.start();
  while (true) {
    // Render image 
    rendering_method_->render(core_);

    // Set image saving flags
    if (saving_image_at_power_of_2_of_pass_ && (pass == saving_pass)) {
      is_image_saving_pass = true;
      saving_pass = saving_pass << 1;
    }

    // Save image
    if (is_image_saving_pass) {
      total_time += timer.elapsedTime();
      saveImage(pass);
      image_data_log << pass << ", " << total_time << endl;
      is_image_saving_pass = false;
      timer.start();
    }

    // Terminate rendering
    if ((pass == termination_pass_) || !manager.isRenderingMode())
      break;

    ++pass;
  }

  emit manager.finishedRendering();
}

/*!
  \details
  No detailed.
  */
void ClRenderer::saveImage(const std::size_t pass)
{
  auto& manager = RendererBase::manager();
  emit manager.outputText(QStringLiteral("Save image"));

  // Convert spectra image to HDR image
  auto& spectra_image = scene_->spectraImageBuffer();
  spectra_image.updateBuffer();
  spectra_image.toHdrImage(pass, *hdr_image_);

  // Convert HDR image to LDR image
  auto& color_system = RendererBase::colorSystem();
  const auto& tonemapping_method = color_system.tonemappingMethod();
  tonemapping_method.tonemap(*hdr_image_, *ldr_image_);

  // Save LDR image
  const auto file_path = manager.outputDirectory() +
                         QStringLiteral("/%1 pass").arg(pass) +
                         ldrImageFormat();
  ldr_image_->save(file_path);

  emit manager.outputImage(*ldr_image_);
}

} // namespace reflect
