/*!
 \file renderer.cpp
 \author takemura
 */

#include "renderer.hpp"
// Standard C++ library
#include <cstdint>
#include <cstddef>
// Qt
#include <QFile>
#include <QObject>
#include <QImage>
#include <QSettings>
#include <QString>
#include <QTextStream>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/stopwatch.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "scene.hpp"
#include "CameraModel/film.hpp"
#include "Color/hdr_image.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_manager.hpp"
#include "RendererBase/renderer_system.hpp"
#include "RenderingMethod/rendering_method.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
Renderer::Renderer(const QSettings& settings) :
    RendererBase(settings)
{
}

/*!
  \details
  No detailed.
  */
Renderer::~Renderer()
{
}

/*!
  \details
  No detailed.
  */
void Renderer::render()
{
  // Initialize
  bool is_image_saving_pass = false;
  std::int64_t image_saving_time = saving_interval_;
  std::size_t pass = 1;
  std::size_t saving_pass = 1;
  std::int64_t total_time = 0;

  zisc::Stopwatch timer;
  auto& manager = RendererBase::manager();

  // Log data
  auto log = makeLogText("log.csv");
  log << "pass,    time (ms),    total time (ms),    time,     total_time" << endl;
  auto image_data_log = makeLogText("image_data.csv");
  image_data_log << "pass,    total time (ms)" << endl;

  while (true) {
    outputPassStartMessage(pass);

    // Render image
    timer.start();
    rendering_method_->render(system());
    const auto pass_time = timer.elapsedTime();

    // Output the rendering time to log
    total_time += pass_time;
    outputPassFinishMessage(pass, pass_time, total_time);
    logRenderingTime(log, pass, pass_time, total_time);

    // Set image saving flags
    if (saving_image_at_power_of_2_of_pass_ && (pass == saving_pass)) {
      is_image_saving_pass = true;
      saving_pass = saving_pass << 1;
    }
    if (image_saving_time < total_time) {
      is_image_saving_pass = true;
      image_saving_time += saving_interval_;
    }

    // Save image
    if (is_image_saving_pass) {
      saveImage(pass);
      image_data_log << pass << ", " << total_time << endl;
      is_image_saving_pass = false;
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
void Renderer::initialize(const QSettings& settings)
{
  scene_ = new Scene{system(), colorSystem(), settings, RendererBase::manager()};
  const auto& film = scene_->film();
  ldr_image_ = new QImage{cast<int>(film.widthResolution()), 
                          cast<int>(film.heightResolution()), 
                          QImage::Format_RGB32};
  hdr_image_ = new HdrImage{film.widthResolution(), film.heightResolution()};

  rendering_method_ = makeRenderingMethod<kWavelengthSampleSize>(system(), 
                                                                 colorSystem(), 
                                                                 settings, 
                                                                 scene_.get());

  const QString system_group{keyword::system_group};
  auto key = system_group + "/" + keyword::spectra_image_saving;
  enable_spectra_image_saving_ = value<bool>(settings, key);

  key = system_group + "/" + keyword::hdr_image_saving;
  enable_hdr_image_saving_ = value<bool>(settings, key);

  key = system_group + "/" + keyword::saving_image_at_power_of_2_of_pass;
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
inline
void Renderer::outputPassFinishMessage(const std::size_t pass,
                                       const std::int64_t pass_time,
                                       const std::int64_t total_time) const
{
  const auto pass_time_text = getTimeText(pass_time);
  const auto total_time_text = getTimeText(total_time);

  const QString finish_meesage{"Finish cycle %1.    time: %2,    total time: %3"};
  auto& manager = RendererBase::manager();
  emit manager.outputText(finish_meesage.arg(pass)
                                        .arg(pass_time_text, total_time_text));
}

/*!
  \details
  No detailed.
  */
inline
void Renderer::outputPassStartMessage(const std::size_t pass) const
{
  const QString start_message{"Start   cycle %1."};
  emit manager().outputText(start_message.arg(pass));
}

/*!
  \details
  No detailed.
  */
void Renderer::saveImage(const std::size_t pass)
{
  auto& manager = RendererBase::manager();
  emit manager.outputText(QStringLiteral("Save image."));

  const auto file_path = manager.renderingDirectory() + 
                         QStringLiteral("/%1_pass").arg(pass);

  const auto& film = scene_->film();
  // Spectra image to HDR image
  const auto& spectra_image = film.spectraBuffer();
  if (enable_spectra_image_saving_)
    spectra_image.save(pass, file_path + ".spectra");
  spectra_image.toHdrImage(system(), colorSystem(), pass, *hdr_image_);
  // HDR image to LDR image
  const auto& tonemapping_method = colorSystem().tonemappingMethod();
  tonemapping_method.tonemap(system(), *hdr_image_, *ldr_image_);
  // Save LDR image
  ldr_image_->save(file_path + ldrImageFormat());

  emit manager.outputImage(*ldr_image_);
}

} // namespace reflect
