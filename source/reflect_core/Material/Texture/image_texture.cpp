/*!
  \file image_texture.cpp
  \author takemura
  */

#include "image_texture.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <vector>
// Qt
#include <QColor>
#include <QImage>
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "texture.hpp"
#include "Color/color_space.hpp"
#include "Color/rgb_color.hpp"
#include "Color/spectral_distribution.hpp"
#include "LinearAlgebra/point.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ImageTexture::ImageTexture(const ColorSystem& color_system,
                           const QSettings& settings, 
                           const QString& prefix)
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
double ImageTexture::floatValue(const Point2& coordinate) const
{
  const auto x = cast<std::size_t>(coordinate[0] * width_);
  const auto y = cast<std::size_t>(coordinate[1] * height_);
  const std::size_t index = width_resolution_ * y + x;
  return float_table_[color_index_[index]];
}

/*!
  \details
  No detailed.
  */
TextureType ImageTexture::type() const
{
  return TextureType::Image;
}

/*!
  \details
  No detailed.
  */
void ImageTexture::initialize(const ColorSystem& color_system,
                              const QSettings& settings, 
                              const QString& prefix)
{
  const auto file_path = value<QString>(settings, 
                                        prefix + "/" + keyword::image_file);
  const QImage image{file_path};

  const int width = image.width();
  const int height = image.height();
  width_resolution_ = cast<std::size_t>(width);
  width_ = cast<double>(width);
  height_ = cast<double>(height);

  const auto key = QString{keyword::color_group} + "/" + keyword::gamma;
  const double gamma = value<double>(settings, key);

  setColor(color_system, image, gamma);
}

/*!
  \details
  No detailed.
  */
void ImageTexture::setColor(const ColorSystem& color_system,
                            const QImage& image, 
                            const double gamma)
{
  const int width = image.width();
  const int height = image.height();
  const int size = width * height;

  std::vector<QRgb> color_table;
  color_table.resize(size);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const std::size_t index = y * width + x;
      color_table[index] = image.pixel(x, y);
    }
  }
  std::sort(color_table.begin(), color_table.end());
  auto table_end = std::unique(color_table.begin(), color_table.end());

  auto get_color_index = [&color_table, &table_end](const QRgb color)
  {
    auto index = std::lower_bound(color_table.begin(), table_end, color);
    return std::distance(color_table.begin(), index);
  };

  color_index_.resize(size);
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const int index = width * y + x;
      color_index_[index] = get_color_index(image.pixel(x, y));
    }
  }
  color_index_.shrink_to_fit();

  float_table_.reserve(size);
  spectra_table_.reserve(size);
  for (auto iterator = color_table.begin(); iterator != table_end; ++iterator) {
    auto rgb = RgbColor{QColor{*iterator}};
    rgb.gammaCorrection(gamma);
    const double y = rgb.toXyz(getRgbToXyzMatrix(color_system.colorSpace())).y();
    float_table_.emplace_back(zisc::clamp(0.0, 1.0, y));
    spectra_table_.emplace_back((color_system.isRgbRenderingMode())
        ? toRgbSpectra(rgb)
        : toSpectra(color_system, rgb));
  }
  spectra_table_.shrink_to_fit();
}

} // namespace reflect
