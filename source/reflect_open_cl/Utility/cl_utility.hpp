/*!
  \file cl_utility.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_UTILITY_HPP_
#define _REFLECT_CL_UTILITY_HPP_

// Standard C++ library
#include <cstddef>
#include <string>
#include <vector>
// Reflect
#include "OpenCL/cl.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

//! Build the program
void buildProgram(cl::Program& program, const std::string& options);

//! Return the device list
std::vector<cl::Device> getDeviceList(
    const std::vector<cl::Platform>& platform_list,
    const bool use_cpu);

//! Return the device list
std::vector<cl::Device> getDeviceList(const cl::Context& context);

//! Return the max threads supported by the device
std::size_t getDeviceThreads(const cl::Device& device, const cl::Kernel& kernel);

//! Return the platform list
std::vector<cl::Platform> getPlatformList();

//! Load OpenCL source code
std::string loadClSourceCode(const std::string& file_path);

//! Make the buffer
UniquePointer<cl::Buffer> makeBuffer(const std::string& name,
                                     const cl::Context& context,
                                     const cl_mem_flags flags,
                                     const std::size_t size,
                                     void* host_pointer = nullptr);

//! Make the context
UniquePointer<cl::Context> makeContext(std::vector<cl::Device>& device_list);

//! Make the kernel
UniquePointer<cl::Kernel> makeKernel(const cl::Program& program, 
                                     const std::string& name);

//! Make the program
UniquePointer<cl::Program> makeClProgram(const cl::Context& context,
                                         const cl::Program::Sources& source_list);

//! Set the kernel arguments
void setKernelArguments(cl::Kernel& kernel,
                        const std::vector<const cl::Buffer*>& arguments);

//! Test OpenCL
void testOpenCl();

} // namespace reflect

#endif // _REFLECT_CL_UTILITY_HPP_
