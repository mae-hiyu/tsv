/*!
  \file thread_pool.cpp
  \author takemura
  */

#include "thread_pool.hpp"
// Standard C++ library
#include <cstddef>
#include <fstream>
#include <regex>
#include <string>
#include <thread>
#include <utility>
// Zisc
#include "error.hpp"
#include "utility.hpp"
// OS dependent
#if defined(Z_WINDOWS)
#include <windows.h>
#elif defined(Z_MAC)
#include <sys/sysctl.h>
#include <sys/types.h>
#endif

namespace zisc {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ThreadPool::ThreadPool() :
    ThreadPool(std::thread::hardware_concurrency())
{
}

/*!
  \details
  No detailed.
  */
ThreadPool::ThreadPool(const std::size_t num_of_threads) :
    is_finish_{false}
{
  createWorkers(num_of_threads);
}

/*!
  \details
  No detailed.
  */
ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock{queue_mutex_};
    is_finish_ = true;
  }
  condition_.notify_all();
  for (auto& worker : workers_)
    worker.join();
}

/*!
  \details
  No detailed.
  */
std::size_t ThreadPool::physicalCores()
{
#if defined(Z_WINDOWS)
  SYSTEM_INFO system_info;
  GetSystemInfo(&system_info);
  return cast<std::size_t>(system_info.dwNumberOfProcessors);
#elif defined(Z_MAC)
  int num_of_cores = 0;
  std::size_t size = sizeof(num_of_cores);
  sysctlbyname("hw.physicalcpu", &num_of_cores, &size, nullptr, 0);
  return cast<std::size_t>(num_of_cores);
#elif defined(Z_LINUX)
  std::ifstream cpu_info{"/proc/cpuinfo"};
  std::string line;
  //! \todo Fix code to below comment code.
//  const std::regex regex{"cpu cores.*(\\d+)"};
  const std::regex regex{"cpu cores.*"};
  std::smatch result;
  while (std::getline(cpu_info, line)) {
    if (std::regex_match(line, result, regex))
      return cast<std::size_t>(std::stoul(std::string{line.back()}));
//      return cast<std::size_t>(std::stoul(result.str(1)));
  }
  return 1;
#else
  static_assert(false, "## Unsupported OS.");
  return 0;
#endif
}

/*!
  \details
  No detailed.
  */
std::size_t ThreadPool::logicalCores()
{
  return cast<std::size_t>(std::thread::hardware_concurrency());
}

/*!
  \details
  No detailed.
  */
void ThreadPool::createWorkers(const std::size_t num_of_threads)
{
  std::size_t threads = (num_of_threads == 0)
      ? std::thread::hardware_concurrency()
      : num_of_threads;
  workers_.reserve(threads);
  for (int thread_number = 0; thread_number < cast<int>(threads); ++thread_number) {
    auto work = [this, thread_number]()
    {
      while (true) {
        std::unique_lock<std::mutex> lock{queue_mutex_};
        while (!is_finish_ && task_queue_.empty())
          condition_.wait(lock);
        if (is_finish_ && task_queue_.empty())
          return;
        std::function<void (int)> task{std::move(task_queue_.front())};
        task_queue_.pop();
        lock.unlock();
        task(thread_number);
      }
    };
    workers_.emplace_back(work);
  }
}

} // namespace zisc
