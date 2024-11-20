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

XYZSpectraImage::XYZSpectraImage(const std::size_t width, const std::size_t height) :
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

void XYZSpectraImage::clear()
{
  for (auto& pixelx : xbuffer_)
    pixelx.fill(0.0);
  for (auto& pixely : ybuffer_)
    pixely.fill(0.0);
  for (auto& pixelz : zbuffer_)
    pixelz.fill(0.0);

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

void XYZSpectraImage::save(const std::size_t pass, const QString& file_path) const
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
                                xbuffer_.size() * kSpectraSize * sizeof(float);

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
  for (const auto spectra : xbuffer_) {
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
void XYZSpectraImage::toHdrImage(RendererSystem& system,
                              const ColorSystem& color_system,
                              const std::size_t pass, 
                              HdrImage& hdr_image) const
{
  const double averager = 1.0 / static_cast<double>(pass);
  // double x_value = 0;
  // double y_value = 0;
  // double z_value = 0;
  const auto& cmf = color_system.xyzColorMatchingFunction();
  const std::size_t width = widthResolution();
  const std::size_t height = heightResolution();
  for (std::size_t y = 0; y < height; ++y) {
    for (std::size_t index = y * width; index < (y + 1) * width; ++index) {
      hdr_image[index] = cmf.toXyzInEmissiveCase(xbuffer_[index], ybuffer_[index], zbuffer_[index]) * averager;
      // x_value += hdr_image[index].x();
      // y_value += hdr_image[index].y();
      // z_value += hdr_image[index].z();
    }
  }


  // std::function<void (const std::size_t)> to_hdr_image{
  // [this, &hdr_image, averager, &color_system, &x_value, &y_value, &z_value](const std::size_t y)
  // {
  //   const auto& cmf = color_system.xyzColorMatchingFunction();
  //   const std::size_t width = widthResolution();

  //   for (std::size_t index = y * width; index < (y + 1) * width; ++index) {
  //     hdr_image[index] = cmf.toXyzInEmissiveCase(xbuffer_[index], ybuffer_[index], zbuffer_[index]) * averager;
  //     x_value += hdr_image[index].x();
  //     y_value += hdr_image[index].y();
  //     z_value += hdr_image[index].z();
  //   }
  // }};
  
  // std::size_t width = widthResolution();
  // std::size_t height = heightResolution();
  // auto& thread_pool = system.threadPool();
  // constexpr std::size_t start = 0;
  // auto result = thread_pool.loop(std::move(to_hdr_image), start, heightResolution()); 
  // result.get();


  // std::cout << "x : " << x_value / (width * height) << std::endl;
  // std::cout << "y : " << y_value / (width * height) << std::endl;
  // std::cout << "z : " << z_value / (width * height) << std::endl;
  // std::ofstream file("./output.txt");
  // if (file.is_open()) {
  //   for (int i = 0; i < 400; ++i) {
  //       file << i + 380 << " " << xHistgram[i] << "\n";
  //   }
  // file.close();
  // } else {
  //     std::cerr << "Unable to open file";
  // }
}

/*!
  \details
  No detailed.
  */
SpectraImageType SpectraImage::type() const
{
  return SpectraImageType::Spectra;
}

SpectraImageType XYZSpectraImage::type() const
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

void XYZSpectraImage::initialize()
{
  const std::size_t buffer_size = widthResolution() * heightResolution();
  xbuffer_.resize(buffer_size);
  ybuffer_.resize(buffer_size);
  zbuffer_.resize(buffer_size);
}

} // namespace reflect
