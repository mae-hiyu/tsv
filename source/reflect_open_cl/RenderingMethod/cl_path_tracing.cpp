/*!
  \file cl_path_tracing.cpp
  \author takemura
  */

#include "cl_path_tracing.hpp"
// Standard C++ library
#include <cstddef>
#include <string>
#include <vector>
// Reflect
#include "cl_rendering_method.hpp"
#include "scene.hpp"
#include "OpenCL/cl.hpp"
#include "OpenCL/cl_core.hpp"
#include "OpenCL/cl_scene.hpp"
#include "OpenCL/Sampling/cl_sampler.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "Utility/size.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ClPathTracing::ClPathTracing(const QSettings& settings,
                             const ClCore& core,
                             ClScene& scene) :
    ClRenderingMethod(settings, core, scene)
{
  initialize(settings, core, scene);
}

/*!
  \details
  No detailed.
  */
std::size_t ClPathTracing::bufferMemorySize() const
{
  const std::size_t sampler_size = 
      static_cast<const std::size_t*>(render_range_)[0] + 1;
  return methodBufferMemorySize() + 
         sizeof(cl_int) + 
         sampler_size * sizeof(ClSamplerType<ReflectSamplerType>::type);
}

/*!
  \details
  No detailed.
  */
std::size_t ClPathTracing::printMemberData()
{
  std::size_t size = ClRenderingMethod::printMemberData();
  size += PRINT_VARIABLE_DATA(number_buffer_);
  size += PRINT_VARIABLE_DATA(initializer_kernel_);
  size += PRINT_VARIABLE_DATA(render_kernel_);
  size += PRINT_VARIABLE_DATA(initializer_range_);
  size += PRINT_VARIABLE_DATA(render_range_);
  return size;
}

/*!
  \details
  No detailed.
  */
void ClPathTracing::render(ClCore& core)
{
  core.addTask(*initializer_kernel_, initializer_range_);
  core.wait();
  core.addTask(*render_kernel_, render_range_);
  core.wait();
}

/*!
  \details
  No detailed.
  */
void ClPathTracing::initialize(const QSettings& settings, 
                               const ClCore& core,
                               ClScene& scene)
{
  // Make pixel index buffer
  constexpr auto buffer_flag = CL_MEM_READ_WRITE | CL_MEM_HOST_NO_ACCESS;
  constexpr std::size_t memory = sizeof(cl_uint);
  number_buffer_ = makeBuffer("Number", core.context(), buffer_flag, memory);

  auto source_file_list = sourceFileList();
  source_file_list.reserve(source_file_list.size() + 1);
  source_file_list.emplace_back("path_tracing.cl");

  // Build and get kernels
  auto program = core.makeProgram(source_file_list, openClDirectory());
  buildProgram(*program, methodOptions());
  initializer_kernel_ = makeKernel(*program, "initializePathTracing");
  render_kernel_ = makeKernel(*program, "render");

  const std::size_t range_size = getDeviceThreads(core.deviceList().front(),
                                                  *render_kernel_);
  // Set buffer
  setSamplerBuffer(settings, core, range_size + 1);
  const std::vector<const cl::Buffer*> initializer_kernel_arguments{
      &samplerBuffer(),
      &wavelengthSamplerBuffer(),
      number_buffer_.get()};
  setKernelArguments(*initializer_kernel_, initializer_kernel_arguments);
  const std::vector<const cl::Buffer*> render_kernel_arguments{
      &scene.weightBuffer(),
      &scene.weightColorIndexBuffer(),
      &scene.weightFloatBuffer(),
      &scene.weightSpectraBuffer(),
      &scene.surfaceScatteringBuffer(),
      &scene.surfaceSpectraBuffer(),
      &scene.emitterBuffer(),
      &scene.objectBuffer(),
      &scene.lightSourceBuffer(),
      &scene.bvhBuffer(),
      &wavelengthSamplerBuffer(),
      &samplerBuffer(),
      &scene.spectraImageBuffer().buffer(),
      number_buffer_.get()};
  setKernelArguments(*render_kernel_, render_kernel_arguments);

  // Set range
  initializer_range_ = cl::NDRange{1};
  render_range_ = cl::NDRange{range_size};
};

} // namespace reflect
