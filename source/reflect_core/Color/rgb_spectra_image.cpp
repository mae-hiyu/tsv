/*!
  \file rgb_spectra_image.cpp
  \author takemura
  */

#include "rgb_spectra_image.hpp"
// Standard C++ library
#include <cstddef>
#include <future>
#include <vector>
#include <utility>
// Zisc
#include "zisc/error.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "color_space.hpp"
#include "hdr_image.hpp"
#include "rgb_color.hpp"
#include "spectra_image_interface.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
RgbSpectraImage::RgbSpectraImage(const std::size_t width, 
                                 const std::size_t height) :
    SpectraImageInterface(width, height)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void RgbSpectraImage::clear()
{
  for (auto& pixel : buffer_) {
    pixel[0] = 0.0;
    pixel[1] = 0.0;
    pixel[2] = 0.0;
  }
}

/*!
  \details
  No detailed.
  */
void RgbSpectraImage::save(const std::size_t /* pass */, const QString& /* file_path */) const
{
  zisc::raiseError("RgbSpectraImageError: save method is not implemented.");
}

/*!
  \details
  No detailed.
  */
void RgbSpectraImage::toHdrImage(RendererSystem& system,
                                 const ColorSystem& color_system,
                                 const std::size_t pass,
                                 HdrImage& hdr_image) const
{
  const double averager = 1.0 / cast<double>(pass);

  std::function<void (const std::size_t)> to_hdr_image{
  [this, &hdr_image, averager, &color_system](const std::size_t y)
  {
    const auto to_xyz_matrix = getRgbToXyzMatrix(color_system.colorSpace());
    const std::size_t width = widthResolution();
    for (std::size_t index = y * width; index < (y + 1) * width; ++index) {
      const RgbColor rgb{averager * buffer_[index].data()};
      hdr_image[index] = rgb.toXyz(to_xyz_matrix);
    }
  }};

  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  auto result = thread_pool.loop(std::move(to_hdr_image), start, heightResolution());
  result.get();
}

/*!
  \details
  No detailed.
  */
SpectraImageType RgbSpectraImage::type() const
{
  return SpectraImageType::Rgb;
}

/*!
  \details
  No detailed.
  */
void RgbSpectraImage::initialize()
{
  const std::size_t buffer_size = widthResolution() * heightResolution();
  buffer_.resize(buffer_size);
}

} // namespace reflect
