/*!
  \file cl_spectra_image.cpp
  \author takemura
  */

#include "cl_spectra_image.hpp"
// Standard C++ library
#include <cstddef>
#include <functional>
#include <vector>
// Zisc
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "Color/hdr_image.hpp"
#include "Color/spectra_image_interface.hpp"
#include "OpenCL/cl.hpp"
#include "OpenCL/cl_core.hpp"
#include "OpenCL/Color/cl_spectral_distribution.hpp"
#include "OpenCL/Utility/cl_float.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/size.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ClSpectraImage::ClSpectraImage(const ClCore& core,
                               const std::size_t width, 
                               const std::size_t height) :
    SpectraImageInterface(width, height),
    core_{&core}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ClSpectraImage::addRadiance(const std::size_t /* x */,
                                 const std::size_t /* y */,
                                 const SampledSpectra& /* sample */)
{
}

/*!
  \details
  No detailed.
  */
cl::Buffer& ClSpectraImage::buffer()
{
  return *buffer_;
}

/*!
  \details
  No detailed.
  */
std::size_t ClSpectraImage::memorySize() const
{
  const std::size_t device_size = core_->deviceList().size();
  return spectra_.size() * sizeof(ClSpectralDistribution) / device_size;
}

/*!
  \details
  No detailed.
  */
std::size_t ClSpectraImage::printMemberData()
{
  std::size_t size = SpectraImageInterface::printMemberData();
  size += PRINT_VARIABLE_DATA(spectra_);
  size += PRINT_VARIABLE_DATA(buffer_);
  size += PRINT_VARIABLE_DATA(core_);
  return size;
}

/*!
  \details
  No detailed.
  */
void ClSpectraImage::save(const std::size_t /* pass */, const QString& /* file_path */) const
{
}

/*!
  \details
  No detailed.
  */
void ClSpectraImage::toHdrImage(const std::size_t pass,
                                HdrImage& hdr_image) const
{
  const double averager = 1.0 / cast<double>(pass);

  std::function<void (const std::size_t)> to_hdr_image{
  [this, &hdr_image, averager](const std::size_t y)
  {
    const auto& color_system = RendererBase::colorSystem();
    const auto& cmf = color_system.xyzColorMatchingFunction();
    const std::size_t width = widthResolution();
    for (std::size_t index = y * width; index < (y + 1) * width; ++index)
      hdr_image[index] = cmf.toXyzInEmissiveCase(spectra_[index]) * averager;
  }};

  auto& system = RendererBase::system();
  auto& thread_pool = system.threadPool();
  constexpr std::size_t start = 0;
  auto result = thread_pool.loop(std::move(to_hdr_image), start, heightResolution());
  result.get();
}

/*!
  \details
  No detailed.
  */
void ClSpectraImage::updateBuffer()
{
  const std::size_t device_size = core_->deviceList().size();
  const std::size_t size = spectra_.size() / device_size;
  const std::size_t memory = size * sizeof(ClSpectralDistribution);
  const auto& queue_list = core_->queueList();
  for (std::size_t index = 0; index < queue_list.size(); ++index) {
    auto* top = spectra_.data() + size * index;
    queue_list[index].enqueueReadBuffer(*buffer_, CL_TRUE, 0, memory, top);
  }
}

/*!
  \details
  No detailed.
  */
void ClSpectraImage::initialize()
{
  const std::size_t device_size = core_->deviceList().size();

  const std::size_t size = widthResolution() * heightResolution();
  spectra_.resize(size);

  constexpr auto buffer_flag = CL_MEM_READ_WRITE | 
                               CL_MEM_HOST_READ_ONLY |
                               CL_MEM_COPY_HOST_PTR;
  const std::size_t memory = size * sizeof(ClSpectralDistribution) / device_size;
  buffer_ = makeBuffer("SpectraImage", 
                       core_->context(), 
                       buffer_flag, 
                       memory, 
                       spectra_.data());
}

} // namespace reflect
