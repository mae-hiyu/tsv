/*!
  \file cl_utility.cpp
  \author takemura
  */

#include "cl_utility.hpp"
// Standard C++ library
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "OpenCL/cl.hpp"
#include "OpenCL/Color/cl_spectral_distribution.hpp"
#include "OpenCL/Data/cl_light_source_reference.hpp"
#include "OpenCL/Data/cl_object.hpp"
#include "OpenCL/DataStructure/cl_bvh_node.hpp"
#include "OpenCL/Material/cl_emitter_model.hpp"
#include "OpenCL/Material/cl_surface_scattering_model.hpp"
#include "OpenCL/Material/cl_weight.hpp"
#include "OpenCL/Sampling/cl_sampled_wavelengths.hpp"
#include "OpenCL/Utility/cl_float.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
void buildProgram(cl::Program& program, const std::string& options)
{
  const auto result = program.build(options.c_str(), nullptr, nullptr);

  for (const auto& device : program.getInfo<CL_PROGRAM_DEVICES>()) {
    std::string build_log;
    program.getBuildInfo(device, CL_PROGRAM_BUILD_LOG, &build_log);
    if (!build_log.empty())
      std::cout << build_log << std::endl;
  }

  constexpr char error_tag[] = "OpenCL BuildError: ";
  switch (result) {
   case CL_SUCCESS:
    break; 
   case CL_INVALID_DEVICE:
    zisc::raiseError(error_tag, "Devices are not in the list of devices.");
    break;
   case CL_INVALID_BUILD_OPTIONS:
    zisc::raiseError(error_tag, "Build options are invalid.");
    break;
   case CL_INVALID_OPERATION:
    zisc::raiseError(error_tag, "Build has uncompleted.");
    break;
   case CL_COMPILER_NOT_AVAILABLE:
    zisc::raiseError(error_tag, "Compiler is not available.");
    break;
   case CL_BUILD_PROGRAM_FAILURE:
    zisc::raiseError(error_tag, "Building program failed.");
    break;
   case CL_OUT_OF_RESOURCES:
    zisc::raiseError(error_tag, "Resource allocation failed.");
    break;
   case CL_OUT_OF_HOST_MEMORY:
    zisc::raiseError(error_tag, "Host resource allocation failed.");
    break;
   default:
    zisc::raiseError(error_tag, "Other error occured.");
    break;
  }
}

/*!
  \details
  No detailed.
  */
std::vector<cl::Device> getDeviceList(
    const std::vector<cl::Platform>& platform_list,
    const bool use_cpu)
{
  const auto flag = (use_cpu) ? CL_DEVICE_TYPE_CPU : CL_DEVICE_TYPE_GPU;
  std::vector<cl::Device> device_list;
  for (const auto& platform : platform_list) {
    std::vector<cl::Device> platform_device_list;
    const auto result = platform.getDevices(flag, &platform_device_list);

    constexpr char error_tag[] = "OpenCL DeviceError: ";
    switch (result) {
     case CL_SUCCESS:
      break;
     case CL_INVALID_DEVICE_TYPE:
      zisc::raiseError(error_tag, "Type is not a valid value.");
      break;
     case CL_INVALID_ARG_VALUE:
      zisc::raiseError(error_tag, "Device is null.");
      break;
     case CL_DEVICE_NOT_FOUND:
      zisc::raiseError(error_tag, "Device is not found.");
      break;
     default:
      zisc::raiseError(error_tag, "Other error occured.");
      break;
    }

    device_list.insert(device_list.end(),
                       platform_device_list.begin(),
                       platform_device_list.end());
  }

  return device_list;
}

/*!
  \details
  No detailed.
  */
std::vector<cl::Device> getDeviceList(const cl::Context& context)
{
  return context.getInfo<CL_CONTEXT_DEVICES>();
}

/*!
  \details
  No detailed.
  */
std::size_t getDeviceThreads(const cl::Device& device, const cl::Kernel& kernel)
{
  constexpr std::size_t k = 2;

  const std::size_t num_of_units = 
      cast<std::size_t>(device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>());
  std::size_t work_group_size;
  kernel.getWorkGroupInfo(device, 
                          CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, 
                          &work_group_size);
  return k * num_of_units * work_group_size;
}

/*!
  \details
  No detailed.
  */
std::vector<cl::Platform> getPlatformList()
{
  std::vector<cl::Platform> platform_list;
  const auto result = cl::Platform::get(&platform_list);

  constexpr char error_tag[] = "OpenCL PlatformError: ";
  switch (result) {
   case CL_SUCCESS:
    break;
   case CL_INVALID_VALUE:
    zisc::raiseError(error_tag, "Platform initialization failed.");
    break;
   default:
    zisc::raiseError(error_tag, "Other error occured.");
    break;
  }

  return platform_list;
}

/*!
  \details
  No detailed.
  */
std::string loadClSourceCode(const std::string& file_path)
{
  std::ifstream source_file;
  source_file.open(file_path);

  std::stringstream source_code;
  std::string line;
  while (std::getline(source_file, line))
    source_code << line << std::endl;

  return source_code.str();
}

/*!
  \details
  No detailed.
  */
UniquePointer<cl::Buffer> makeBuffer(const std::string& name,
                                     const cl::Context& context,
                                     const cl_mem_flags flags,
                                     const std::size_t size,
                                     void* host_pointer)
{
  constexpr std::size_t int_size = sizeof(cl_int);
  cl_int test_value = 0;

  cl_int result = 0;
  UniquePointer<cl::Buffer> buffer;
  if (size != 0)
    buffer = new cl::Buffer{context, flags, size, host_pointer, &result};
  else if (host_pointer != nullptr)
    buffer = new cl::Buffer{context, flags, int_size, nullptr, &result};
  else
    buffer = new cl::Buffer{context, flags, int_size, &test_value, &result};

  const auto error_tag = "OpenCL BufferError: " + name + ": ";
  switch (result) {
   case CL_SUCCESS:
    break;
   case CL_INVALID_CONTEXT:
    zisc::raiseError(error_tag, "Context is not a valid context.");
    break;
   case CL_INVALID_VALUE:
    zisc::raiseError(error_tag, "Flags are not valid.");
    break;
   case CL_INVALID_BUFFER_SIZE:
    zisc::raiseError(error_tag, "Size is 0.");
    break;
   case CL_INVALID_HOST_PTR:
    zisc::raiseError(error_tag, "Host pointer is null.");
    break;
   case CL_MEM_OBJECT_ALLOCATION_FAILURE:
    zisc::raiseError(error_tag, "Buffer memory allocation failed.");
    break;
   case CL_OUT_OF_RESOURCES:
    zisc::raiseError(error_tag, "Resouce allocation failed.");
    break;
   case CL_OUT_OF_HOST_MEMORY:
    zisc::raiseError(error_tag, "Host resource allocation failed.");
    break;
   default:
    zisc::raiseError(error_tag, "Other error occured.");
    break;
  }

  return buffer;
}

/*!
  \details
  No detailed.
  */
UniquePointer<cl::Context> makeContext(std::vector<cl::Device>& device_list)
{
  cl_int result = 0;
  UniquePointer<cl::Context> context{
      new cl::Context{device_list, nullptr, nullptr, nullptr, &result}};

  constexpr char error_tag[] = "OpenCL ContextError: ";
  switch (result) {
   case CL_SUCCESS:
    break;
   case CL_INVALID_PROPERTY:
    zisc::raiseError(error_tag, "Property name is not a supported property name.");
    break;
   case CL_INVALID_VALUE:
    zisc::raiseError(error_tag, "The length of device is zero.");
    break;
   case CL_DEVICE_NOT_AVAILABLE:
    zisc::raiseError(error_tag, "Device is not available.");
    break;
   case CL_OUT_OF_HOST_MEMORY:
    zisc::raiseError(error_tag, "Resource allocation failed.");
    break;
   default:
    zisc::raiseError(error_tag, "Other error occured.");
    break;
  }

  return context;
}

/*!
  \details
  No detailed.
  */
UniquePointer<cl::Kernel> makeKernel(const cl::Program& program, 
                                     const std::string& name)
{
  cl_int result = 0;
  UniquePointer<cl::Kernel> kernel{
      new cl::Kernel{program, name.c_str(), &result}};

  constexpr char error_tag[] = "OpenCL KernelError: ";
  switch (result) {
   case CL_SUCCESS:
    break;
   case CL_INVALID_PROGRAM:
    zisc::raiseError(error_tag, "Program is not valid.");
    break;
   case CL_INVALID_PROGRAM_EXECUTABLE:
    zisc::raiseError(error_tag, "No successfully build executable.");
    break;
   case CL_INVALID_KERNEL_NAME:
    zisc::raiseError(error_tag, name, " is not found in program.");
    break;
   case CL_INVALID_KERNEL_DEFINITION:
    zisc::raiseError(error_tag, name, 
                     " kernel arguments are not same for all devices");
    break;
   case CL_INVALID_VALUE:
    zisc::raiseError(error_tag, "Name is null.");
    break;
   case CL_OUT_OF_RESOURCES:
    zisc::raiseError(error_tag, "Resource allocation failed.");
    break;
   case CL_OUT_OF_HOST_MEMORY:
    zisc::raiseError(error_tag, "Host resource allocation failed.");
    break;
   default:
    zisc::raiseError(error_tag, "code: ", result, ", Other error occured.");
    break;
  }

  return kernel;
}

/*!
  \details
  No detailed.
  */
UniquePointer<cl::Program> makeClProgram(const cl::Context& context,
                                         const cl::Program::Sources& source_list)
{
  cl_int result = 0;
  UniquePointer<cl::Program> program{
      new cl::Program{context, source_list, &result}};

  constexpr char error_tag[] = "OpenCL ProgramError: ";
  switch (result) {
   case CL_SUCCESS:
    break;
   case CL_INVALID_CONTEXT:
    zisc::raiseError(error_tag, "Context is not a valid context.");
    break;
   case CL_INVALID_VALUE:
    zisc::raiseError(error_tag, "Source list is empty.");
    break;
   case CL_OUT_OF_HOST_MEMORY:
    zisc::raiseError(error_tag, "Host resource allocation failed.");
    break;
   default:
    zisc::raiseError(error_tag, "Other error occured.");
    break;
  }

  return program;
}

/*!
  \details
  No detailed.
  */
void setKernelArguments(cl::Kernel& kernel,
                        const std::vector<const cl::Buffer*>& arguments)
{
  std::size_t index = 0;
  for (const auto* argument : arguments) {
    const auto result = kernel.setArg(index, *argument);
    const auto error_tag = "OpenCL KernelArguemtnError: argument index " + 
                           std::to_string(index) + "in " + 
                           kernel.getInfo<CL_KERNEL_FUNCTION_NAME>() + ": ";
    switch (result) {
     case CL_SUCCESS:
      break;
     case CL_INVALID_ARG_INDEX:
      zisc::raiseError(error_tag, "Not a valid argument index.");
      break;
     case CL_INVALID_MEM_OBJECT:
      zisc::raiseError(error_tag, "Not a valid memory object.");
      break;
     case CL_INVALID_SAMPLER:
      zisc::raiseError(error_tag, "Not a valid sampler object.");
      break;
     default:
      zisc::raiseError(error_tag, "Other error occured.");
      break;
    }
    ++index;
  }
}

/*!
 \details
 No detailed.
 */
//void testOpenCl()
//{
//  const auto platform_list = getPlatformList();
//  auto device_list = getDeviceList(platform_list, false);
//  const auto context = makeContext(device_list);
//  cl::CommandQueue queue{*context, device_list[0]};
//
//  // Make program
//  const auto code = loadClSourceCode("OpenCL/test.cl");
//  cl::Program::Sources source_code;
//  source_code.reserve(1);
//  source_code.emplace_back(std::make_pair(code.c_str(), code.size()));
//  auto program = makeProgram(*context, source_code);
//
//  // Build program
//  const std::string options{" -I OpenCL"
//                            " -D REFLECT_XSADD_SAMPLER"
//                            " -D REFLECT_WIDTH_RESOLUTION=640"
//                            " -D REFLECT_HEIGHT_RESOLUTION=480"
//                            " -D REFLECT_EMITTER_SIZE=1"
//                            " -D REFLECT_LIGHT_SOURCE_SIZE=1"
//                            " -D REFLECT_NON_OBJECT_INDEX=1"};
//  buildProgram(*program, options);
//  std::cout << "## Test code build successed." << std::endl;
//
//  cl::NDRange range{1};
//  // Test1
//  std::cout << "## Start test1" << std::endl;
//  {
//    // Make buffers
//    constexpr auto buffer_flag = CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY;
//    constexpr std::size_t buffer_size = 10;
//    constexpr std::size_t buffer_memory = buffer_size * sizeof(cl_int);
//    auto buffer = makeBuffer("Size", *context, buffer_flag, buffer_memory, nullptr);
//  
//    // Execute test
//    const std::vector<const cl::Buffer*> arguments{buffer.get()};
//    auto kernel = makeKernel(*program, "sizeTest");
//    setKernelArguments(*kernel, arguments);
//    queue.enqueueNDRangeKernel(*kernel, cl::NullRange, range, cl::NullRange);
//    queue.finish();
//    cl_int result[buffer_size];
//    queue.enqueueReadBuffer(*buffer, CL_TRUE, 0, buffer_memory, result);
//    const auto check_size = [](const std::size_t host_size,
//                               const int device_size,
//                               const std::string& name)
//    {
//      if (static_cast<int>(host_size) != device_size) {
//        std::cout << "## " << name << ": Host = " << host_size 
//                                   << ", Device = " << device_size << std::endl;
//      }
//    };
//    check_size(sizeof(ClBvhNode), result[0], "BvhNode");
//    check_size(sizeof(ClEmitterModel), result[1], "EmitterModel");
//    check_size(sizeof(ClLightSourceReference), result[2], "LightSourceReference");
//    check_size(sizeof(ClObject), result[3], "Object");
//    check_size(sizeof(ClSampledWavelengths), result[4], "SampledWavelengths");
//    check_size(sizeof(ClSurfaceScatteringModel), result[5], "SurfaceScatteringModel");
//    check_size(sizeof(ClSpectralDistribution), result[6], "SpectralDistribution");
//    check_size(sizeof(ClWeight), result[7], "Weight");
//  }
//  std::cout << "## Finish test1" << std::endl;
//
//  // Test2
//  std::cout << "## Start test2" << std::endl;
//  {
//    // Make buffers
//    constexpr auto buffer_flag = CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY;
//    constexpr std::size_t buffer_size = 4;
//    constexpr std::size_t float_memory = buffer_size * sizeof(cl_float);
//    auto buffer1 = makeBuffer("Float", *context, buffer_flag, float_memory, nullptr);
//    constexpr std::size_t half_memory = buffer_size * sizeof(cl_half);
//    auto buffer2 = makeBuffer("Half", *context, buffer_flag, half_memory, nullptr);
//
//    // Execute test
//    const std::vector<const cl::Buffer*> arguments{buffer1.get(), buffer2.get()};
//    auto initializer = makeKernel(*program, "initializeFloatTest");
//    setKernelArguments(*initializer, arguments);
//    queue.enqueueNDRangeKernel(*initializer, cl::NullRange, range, cl::NullRange);
//    queue.finish();
//    auto kernel = makeKernel(*program, "floatTest");
//    setKernelArguments(*kernel, arguments);
//    queue.enqueueNDRangeKernel(*kernel, cl::NullRange, range, cl::NullRange);
//    queue.finish();
//    cl_float result1[4];
//    queue.enqueueReadBuffer(*buffer1, CL_TRUE, 0, float_memory, result1);
//    cl_half result2[4];
//    queue.enqueueReadBuffer(*buffer2, CL_TRUE, 0, half_memory, result2);
//    auto test_float = [result1]()
//    {
//      for (std::size_t index = 0; index < 4; ++index) {
//        const float v = std::round(static_cast<float>(2 * index));
//        const float r = std::round(result1[index]);
//        if (r != v) {
//          std::cout << "## Float test failed."
//                    << " Host: " << v << ", Device: " << r << std::endl;
//        }
//      }
//    };
//    test_float();
//    auto test_half = [result2]()
//    {
//      for (std::size_t index = 0; index < 4; ++index) {
//        const float v = std::round(static_cast<float>(2 * index));
//        const float r = std::round(toFloat(result2[index]));
//        if (r != v) {
//          std::cout << "## Half test failed."
//                    << " Host: " << v << ", Device: " << r << std::endl;
//        }
//      }
//    };
//    test_half();
//  }
//  std::cout << "## Finish test2" << std::endl;
//}

} // namespace reflect
