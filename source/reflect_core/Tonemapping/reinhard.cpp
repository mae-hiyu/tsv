/*!
  \file reinhard.cpp
  \author takemura
  */

#include "reinhard.hpp"
// Standard C++ library
#include <cmath>
#include <limits>
// Qt
#include <QSettings>
#include <QString>
#include <QImage>
// Zisc
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "reflect_config.hpp"
#include "tonemapping_method.hpp"
#include "Color/hdr_image.hpp"
#include "Color/xyz_color.hpp"
#include "Color/yxy_color.hpp"
#include "RendererBase/renderer_system.hpp"

namespace reflect {

using zisc::cast;


/*!
  \details
  No detailed.
  */
Reinhard::Reinhard(const QSettings& settings, const QString& prefix) :
    TonemappingMethod(settings, prefix)
{
  setKey(0.18);
}

/*!
  \details
  No detailed.
  */
void Reinhard::setKey(const double key_value)
{
  key_ = key_value;
}

/*!
  \details
  No detailed.
  */
void Reinhard::tonemap(RendererSystem& /* system */,
                       const HdrImage& /* hdr_image */, 
                       QImage& /* ldr_image */) const
{
////  constexpr double delta = std::numeric_limits<double>::epsilon();
//  constexpr double delta = cast<double>(5.0e-1);
//  std::cout << "## Delta: " << delta << std::endl;
//  double log_sum_luminace = _0;
//  for (const auto& xyz : hdr_image) {
//    log_sum_luminace += std::log(delta + xyz.getY());
//  }
////  const double log_average_luminace = std::exp(log_sum_luminace) /
////                                     cast<double>(hdr_image.size());
//  std::cout << "## Sum: " << log_sum_luminace << std::endl;
//  std::cout << "## Exp: " << std::exp(log_sum_luminace) << std::endl;
//  const double inverse_average_luminance = cast<double>(hdr_image.size()) /
//                                          std::exp(log_sum_luminace);
//  const double coefficient = key_ * inverse_average_luminance;
//  std::cout << "## Coefficient: " << coefficient << std::endl;
//  for (int y = 0; y < ldr_image.height(); ++y) {
//    for (int x = 0; x < ldr_image.width(); ++x) {
//      auto&& yxy = hdr_image[x + (y * ldr_image.width())].toYxy();
//      const double scaled_luminance = coefficient * yxy.getY();
//      yxy.setY(zisc::clamp(_0, _1, scaled_luminance / (_1 * scaled_luminance)));
////      auto rgb = yxy.toXyz().toQRgb();
////      std::cout << "## Red: " << qRed(rgb) << std::endl;
////      std::cout << "## Green: " << qGreen(rgb) << std::endl;
////      std::cout << "## Blue: " << qBlue(rgb) << std::endl;
//      ldr_image.setPixel(x, y, yxy.toXyz().toQRgb());
//    }
//  }
}

} // namespace reflect
