/*!
  \file cl_core.cpp
  \author takemura
  */

#include "cl_core.hpp"
// Standard C++ library
#include <cstddef>
#include <string>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Reflect
#include "cl.hpp"
#include "keyword.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ClCore::ClCore(const QSettings& settings)
{
  initialize(settings);
}

/*!
  \details
  No detailed.
  */
void ClCore::addTask(const cl::Kernel& kernel, const cl::NDRange& range)
{
  for (std::size_t id = 0; id < queue_list_.size(); ++id) {
    auto& queue = queue_list_[id];
    queue.enqueueNDRangeKernel(kernel, cl::NDRange{id}, range, cl::NullRange);
  }
}

/*!
  \details
  No detailed.
  */
const cl::Context& ClCore::context() const
{
  return *context_;
}

/*!
  \details
  No detailed.
  */
const std::vector<cl::Device>& ClCore::deviceList() const
{
  return device_list_;
}

/*!
  \details
  No detailed.
  */
UniquePointer<cl::Program> ClCore::makeProgram(
    const std::vector<std::string>& source_file_list,
    const std::string& file_path) const
{
  // Load source code
  std::vector<std::string> source_code_list;
  source_code_list.reserve(source_file_list.size());
  for (const auto& file_name : source_file_list) {
    const auto path = file_path + "/" + file_name;
    auto code = loadClSourceCode(path);
    source_code_list.emplace_back(std::move(code));
  }
  // Make a program from source code list
  cl::Program::Sources source_code;
  source_code.reserve(source_code_list.size());
  for (const auto& code : source_code_list)
    source_code.emplace_back(std::make_pair(code.c_str(), code.size()));
  return makeClProgram(*context_, source_code);
}

/*!
  \details
  No detailed.
  */
void ClCore::initialize(const QSettings& settings)
{
  auto key = QString{keyword::system_group} + "/" + keyword::open_cl_cpu;
  const bool use_cpu = value<bool>(settings, key);
  key = QString{keyword::system_group} + "/" + keyword::open_cl_use_multiple_gpus;
  const bool use_multiple_gpus = value<bool>(settings, key);

  platform_list_ = getPlatformList();
  device_list_ = getDeviceList(platform_list_, use_cpu);
  if (!use_multiple_gpus) {
    while (device_list_.size() != 1)
      device_list_.pop_back();
  }
  context_ = makeContext(device_list_);
  queue_list_.reserve(device_list_.size());
  for (const auto& device : device_list_)
    queue_list_.emplace_back(*context_, device);
}

/*!
  \details
  No detailed.
  */
const std::vector<cl::Platform>& ClCore::platformList() const
{
  return platform_list_;
}

/*!
  \details
  No detailed.
  */
void ClCore::wait()
{
  for (auto& queue : queue_list_)
    queue.finish();
}

} // namespace reflect
