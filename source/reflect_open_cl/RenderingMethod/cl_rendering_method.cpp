/*!
  \file cl_rendering_method.cpp
  \author takemura
  */

#include "cl_rendering_method.hpp"
// Standard C++ library
#include <cstddef>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
// Qt
#include <QDir>
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "cl_path_tracing.hpp"
#include "reflect_config.hpp"
#include "scene.hpp"
#include "DataStructure/bvh_node.hpp"
#include "OpenCL/cl.hpp"
#include "OpenCL/cl_core.hpp"
#include "OpenCL/Sampling/cl_sampled_wavelengths.hpp"
#include "OpenCL/Sampling/cl_sampler.hpp"
#include "OpenCL/Utility/cl_float.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_system.hpp"
#include "Sampling/sampled_wavelengths.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ClRenderingMethod::ClRenderingMethod(const QSettings& settings,
                                     const ClCore& core,
                                     ClScene& scene)
{
  initialize(settings, core, scene);
}

/*!
  \details
  No detailed.
  */
std::string ClRenderingMethod::getRussianRouletteOptions(
    const QSettings& settings) const
{
  std::string options;
  const auto prefix = 
      QString{keyword::rendering_method} + "/" + keyword::russian_roulette;
  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::path_length):
    options += " -D REFLECT_RUSSIAN_ROULETTE_PATH_LENGTH";
    options += " -D REFLECT_PATH_LENGTH=" + std::to_string(
      value<std::size_t>(settings, prefix + "/" + keyword::path_length_max));
    break;
   case zisc::toHash32(keyword::reflectance_average): 
    options += " -D REFLECT_RUSSIAN_ROULETTE_AVERAGE";
    break;
   case zisc::toHash32(keyword::reflectance_max):
    options += " -D REFLECT_RUSSIAN_ROULETTE_MAX";
    break;
   default:
    zisc::raiseError("RussianRouletteOptionError: Unsupported option.");
    break;
  }
  return options;
}

/*!
  \details
  No detailed.
  */
std::string ClRenderingMethod::getWavelengthSamplerOptions(
    const QSettings& settings) const
{
  std::string options;

  const auto key = QString{keyword::color_group} + "/" + keyword::spectrum_sampling;
  const auto method = value<QString>(settings, key);
  switch (zisc::toHash32(method.toStdString().c_str())) {
   case zisc::toHash32(keyword::regular_sampling):
    options = " -D REFLECT_WAVELENGTH_REGULAR_SAMPLING";
    break;
   case zisc::toHash32(keyword::random_sampling):
    options = " -D REFLECT_WAVELENGTH_RANDOM_SAMPLING";
    break;
   case zisc::toHash32(keyword::stratified_sampling):
    options = " -D REFLECT_WAVELENGTH_STRATIFIED_SAMPLING";
    break;
   default:
    break;
  }
  return options;
}

/*!
  \details
  No detailed.
  */
void ClRenderingMethod::initialize(const QSettings& settings,
                                   const ClCore& core,
                                   ClScene& scene)
{
  // Wavelength sampler
  constexpr auto buffer_flag = CL_MEM_READ_WRITE | CL_MEM_HOST_NO_ACCESS;
  wavelength_sampler_buffer_ = makeBuffer("WavelengthSampler",
                                           core.context(),
                                           buffer_flag,
                                           sizeof(ClSampledWavelengths));
  
  // Set options
  method_options_ += scene.buildOptions();
  method_options_ += getWavelengthSamplerOptions(settings);
  method_options_ += getSamplerOptions<ReflectSamplerType>();
  method_options_ += getRussianRouletteOptions(settings);
  method_options_ += " -D REFLECT_NON_OBJECT_INDEX=" + 
                     std::to_string(BvhNode::kNonObjectIndex);
  method_options_ += " -I " + openClDirectory();
}

/*!
  \details
  No detailed.
  */
std::size_t ClRenderingMethod::methodBufferMemorySize() const
{
  return sizeof(ClSampledWavelengths);
}

/*!
  \details
  No detailed.
  */
const std::string& ClRenderingMethod::methodOptions() const
{
  return method_options_;
}

/*!
  \details
  No detailed.
  */
std::size_t ClRenderingMethod::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(wavelength_sampler_buffer_);
  size += PRINT_VARIABLE_DATA(sampler_buffer_);
  size += PRINT_VARIABLE_DATA(method_options_);
  return size;
}

/*!
  \details
  No detailed.
  */
std::vector<std::string> ClRenderingMethod::sourceFileList() const
{
  return std::vector<std::string>{
      getSamplerSource<ReflectSamplerType>(),
      "bvh_node.cl",
      "bvh.cl",
      "camera.cl",
      "emitter_model.cl",
      "film.cl",
      "light_source_reference.cl",
      "object.cl",
      "rendering_method.cl",
      "russian_roulette.cl",
      "sampled_direction.cl",
      "sampled_spectra.cl",
      "sampled_wavelengths.cl",
      "spectral_distribution.cl",
      "surface_scattering_model.cl",
      "vector.cl",
      "weight.cl"};
}

/*!
  \details
  No detailed.
  */
void ClRenderingMethod::setSamplerBuffer(const QSettings& settings,
                                         const ClCore& core,
                                         const std::size_t size)
{
  // Initialize sampler buffer 
  sampler_buffer_ = makeSamplerBuffer<ReflectSamplerType>(settings, core, size);
}

/*!
  \details
  No detailed.
  */
const cl::Buffer& ClRenderingMethod::wavelengthSamplerBuffer() const
{
  return *wavelength_sampler_buffer_;
}

/*!
  \details
  No detailed.
  */
cl::Buffer& ClRenderingMethod::samplerBuffer()
{
  return *sampler_buffer_;
}

/*!
  \details
  No detailed.
  */
std::string ClRenderingMethod::openClDirectory() const
{
  return (QDir::currentPath() + "/OpenCL").toStdString();
}

/*!
  \details
  No detailed.
  */
UniquePointer<ClRenderingMethod> makeClRenderingMethod(
    const QSettings& settings,
    const ClCore& core,
    ClScene& scene)
{
  ClRenderingMethod* method = nullptr;

  const auto key = QString{keyword::rendering_method_group} + "/" +
                   keyword::rendering_method;
  const auto method_type = value<QString>(settings, key);
  switch (zisc::toHash32(method_type.toStdString().c_str())) {
   case zisc::toHash32(keyword::path_tracing_method):
    method = new ClPathTracing{settings, core, scene};
    break;
   default:
    zisc::raiseError("ClRenderingMethodError: Unsupported type is specified.");
    break;
  }
  return UniquePointer<ClRenderingMethod>{method};
}

} // namespace reflect
