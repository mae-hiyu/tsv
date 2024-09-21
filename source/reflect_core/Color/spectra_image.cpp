/*!
  \file spectra_image.cpp
  \author takemura
  */

#include "spectra_image.hpp"
// Standard C++ library
#include <cstdint>
#include <cstddef>
#include <functional>
#include <vector>
// Qt
#include <QByteArray>
#include <QFile>
// Zisc
#include "zisc/binary_file.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "color_space.hpp"
#include "hdr_image.hpp"
#include "reflect_config.hpp"
#include "rgb_color.hpp"
#include "spectral_distribution.hpp"
#include "xyz_color.hpp"
#include "xyz_color_matching_function.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Utility/file.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SpectraImage::SpectraImage(const std::size_t width, const std::size_t height) :
    SpectraImageInterface(width, height)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SpectraImage::clear()
{
  for (auto& pixel : buffer_)
    pixel.fill(0.0);
}

/*!
  \details
  No detailed.
  */
void SpectraImage::save(const std::size_t pass, const QString& file_path) const
{
  // Image resolution
  const std::uint32_t width = widthResolution();
  const std::uint32_t height = heightResolution();
  // Spectra information
  constexpr std::uint16_t lambda_min = kShortestWavelength;
  constexpr std::uint16_t delta_lambda = kWavelengthResolution;
  constexpr std::uint16_t n = kSpectraSize;
  // Floating point information
  constexpr std::uint8_t float_type = 0;
  // Calculate image byte size
  constexpr std::size_t header_byte_size = 4 * 2 + 2 * 3 + 1;
  const std::size_t byte_size = header_byte_size + 
                                buffer_.size() * kSpectraSize * sizeof(float);

  // Create spectra row data
  QByteArray spectra_row_data;
  spectra_row_data.reserve(byte_size);

  // Write data
  write(&spectra_row_data, width);
  write(&spectra_row_data, height);
  write(&spectra_row_data, lambda_min);
  write(&spectra_row_data, delta_lambda);
  write(&spectra_row_data, n);
  write(&spectra_row_data, float_type);
  const double k = 1.0 / cast<double>(pass);
  for (const auto spectra : buffer_) {
    for (std::size_t i = 0; i < spectra.size(); ++i) {
      const float data = k * spectra[i];
      write(&spectra_row_data, data);
    }
  }

  // Compress and save image
  QFile spectra_image{file_path};
  spectra_image.open(QIODevice::WriteOnly);
//  const auto compressed_data = qCompress(spectra_row_data, -1);
//  spectra_image.write(compressed_data);
  spectra_image.write(spectra_row_data);
  spectra_image.close();
}

/*!
  \details
  No detailed.
  */
void SpectraImage::toHdrImage(RendererSystem& system,
                              const ColorSystem& color_system,
                              const std::size_t pass, 
                              HdrImage& hdr_image) const
{
  const double averager = 1.0 / cast<double>(pass);

  std::function<void (const std::size_t)> to_hdr_image{
  [this, &hdr_image, averager, &color_system](const std::size_t y)
  {
    const auto& cmf = color_system.xyzColorMatchingFunction();
    const std::size_t width = widthResolution();
    for (std::size_t index = y * width; index < (y + 1) * width; ++index)
      hdr_image[index] = cmf.toXyzInEmissiveCase(buffer_[index]) * averager;
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
SpectraImageType SpectraImage::type() const
{
  return SpectraImageType::Spectra;
}

/*!
  \details
  No detailed.
  */
void SpectraImage::initialize()
{
  const std::size_t buffer_size = widthResolution() * heightResolution();
  buffer_.resize(buffer_size);
}

} // namespace reflect
