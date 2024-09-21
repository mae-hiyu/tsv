/*!
  \file cl_core.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_CORE_HPP_
#define _REFLECT_CL_CORE_HPP_

// Standard C++ library
#include <string>
#include <vector>
// Reflect
#include "cl.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ClCore
{
 public:
  //! Make a instance
  ClCore(const QSettings& settings);


  //! Add a task
  void addTask(const cl::Kernel& kernel, const cl::NDRange& range);

  //! Return the context
  const cl::Context& context() const;

  //! Return the device list
  const std::vector<cl::Device>& deviceList() const;

  //! Make a program from source files
  UniquePointer<cl::Program> makeProgram(
      const std::vector<std::string>& source_file_list,
      const std::string& file_path) const;

  //! Return the platform list
  const std::vector<cl::Platform>& platformList() const;

  //! Return the queue list
  const std::vector<cl::CommandQueue>& queueList() const;

  //! Wait to finish all tasks
  void wait();

 private:
  //! Initialize
  void initialize(const QSettings& settings);


  std::vector<cl::Platform> platform_list_;
  std::vector<cl::Device> device_list_;
  std::vector<cl::CommandQueue> queue_list_;
  UniquePointer<cl::Context> context_;
};

} // namespace reflect

#endif // _REFLECT_CL_CORE_HPP_
