/*!
  \file thread_pool.hpp
  \author takemura
  */

#ifndef _ZISC_THREAD_POOL_HPP_
#define _ZISC_THREAD_POOL_HPP_

// Standard C++ library
#include <cstddef>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace zisc {

/*!
  \brief 
  \details
  ThreadPool class is designed based on http://progsch.net/wordpress/?p=81
  and https//github.com/progschj/ThreadPool.
  */
class ThreadPool
{
 public:
  //! Create threads as many CPU threads as
  ThreadPool();

  //! Create threads
  ThreadPool(const std::size_t num_of_threads);

  //! Terminate threads
  ~ThreadPool();


  //! Add task
  template <typename Type>
  std::future<Type> enqueue(std::function<Type (void)>&& task);

  //! Add task and a thread number is delivered
  template <typename Type>
  std::future<Type> enqueue(std::function<Type (int)>&& task);

  //! Get the number of logical cores
  static std::size_t logicalCores();

  //! Execute loop task in parallel
  template <typename Integer>
  std::future<void> loop(std::function<void (Integer)>&& task, 
                         Integer begin, 
                         Integer end);

  //! Execute loop task in parallel
  template <typename Integer>
  std::future<void> loop(std::function<void (int, Integer)>&& task, 
                         Integer begin, 
                         Integer end);

  //! Get the number of threads
  std::size_t numOfThreads() const;

  //! Get the number of physical cores
  static std::size_t physicalCores();

 private:
  //! Create worker threads
  void createWorkers(const std::size_t num_of_threads);


  std::vector<std::thread> workers_;
  std::queue<std::function<void (int)>> task_queue_;
  std::condition_variable condition_;
  std::mutex queue_mutex_;
  bool is_finish_;
};

} // namespace zisc

#include "thread_pool-inl.hpp"

#endif // _ZISC_THREAD_POOL_HPP_
