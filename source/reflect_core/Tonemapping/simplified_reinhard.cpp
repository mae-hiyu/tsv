/*!
  \file simplified_reinhard.cpp
  \author takemura
  */

#include "simplified_reinhard.hpp"
// Standard C++ library
#include <functional>
#include <future>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
#include <QImage>
// Zisc
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "tonemapping_method.hpp"
#include "Color/rgb_color.hpp"
#include "Color/hdr_image.hpp"
#include "Color/xyz_color.hpp"
#include "Color/yxy_color.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SimplifiedReinhard::SimplifiedReinhard(const QSettings& settings,
                                       const QString& prefix) :
    TonemappingMethod(settings, prefix)
{
}

/*!
  \details
  No detailed.
  */
void SimplifiedReinhard::tonemap(RendererSystem& system,
                                 const HdrImage& hdr_image, 
                                 QImage& ldr_image) const
{
  std::function<void (const int)> tonemap_image{
  [this, &hdr_image, &ldr_image](const int y)
  {
    std::size_t index = cast<std::size_t>(y * ldr_image.width());
    for (int x = 0; x < ldr_image.width(); ++x) {
      // Set black if radiance is zero
      if (hdr_image[index].y() == 0.0) {
        ldr_image.setPixel(x, y, 0);
        ++index;
        continue;
      }
      
      auto yxy = hdr_image[index].toYxy();
      yxy.Y() = zisc::clamp(0.0, 1.0, yxy.Y() / (1.0 + yxy.Y()));
      const auto xyz = yxy.toXyz();
      auto rgb = xyz.toRgb(toRgbMatrix());
      if (1.0 < rgb.max())
        rgb.scale();
      rgb.clamp();
      rgb.gammaCorrection(inverseGamma());
      ldr_image.setPixel(x, y, rgb.toQRgb());
      ++index;
    }
  }};

  auto& thread_pool = system.threadPool();
  auto result = thread_pool.loop(std::move(tonemap_image), 0, ldr_image.height());
  result.get();
}

} // namespace reflect
