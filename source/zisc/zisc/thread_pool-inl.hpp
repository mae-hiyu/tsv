/*!
  \file thread_pool-inl.hpp
  \author takemura
  */

#ifndef _ZISC_THREAD_POOL_INL_HPP_
#define _ZISC_THREAD_POOL_INL_HPP_

#include "thread_pool.hpp"
// Standard C++ library
#include <atomic>
#include <cmath>
#include <functional>
#include <future>
#include <memory>
#include <type_traits>
#include <queue>
#include <utility>
// Zisc
#include "utility.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Type> inline
std::future<Type> ThreadPool::enqueue(std::function<Type (void)>&& task)
{
  auto shared_task = std::make_shared<std::packaged_task<Type ()>>(std::move(task));
  auto wrapped_task = [shared_task](const int /* thread_number */)
  {
    (*shared_task)();
  };

  auto result = shared_task->get_future();
  {
    std::unique_lock<std::mutex> lock{queue_mutex_};
    task_queue_.emplace(wrapped_task);
  }
  condition_.notify_one();

  return result;
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
std::future<Type> ThreadPool::enqueue(std::function<Type (int)>&& task)
{
  auto shared_task = std::make_shared<std::packaged_task<Type(int)>>(std::move(task));
  auto wrapped_task = [shared_task](const int thread_number)
  {
    (*shared_task)(thread_number);
  };

  auto result = shared_task->get_future();
  {
    std::unique_lock<std::mutex> lock{queue_mutex_};
    task_queue_.emplace(wrapped_task);
  }
  condition_.notify_one();

  return result;
}

/*!
  \details
  No detailed.
  */
template <typename Integer>
std::future<void> ThreadPool::loop(std::function<void (Integer)>&& task, 
                                   Integer begin, 
                                   Integer end)
{
  static_assert(std::is_integral<Integer>::value,
                "## Integer must be integer type.");

  auto shared_task = new std::function<void (Integer)>{std::move(task)};
  auto finish_loop = new std::packaged_task<void ()>{[](){}};
  const int distance = cast<int>(end - begin);
  auto shared_counter = new std::atomic_int{distance};

  auto finish = [shared_task, finish_loop, shared_counter]()
  {
    (*finish_loop)();
    delete shared_counter;
    delete finish_loop;
    delete shared_task;
  };

  auto result = finish_loop->get_future();

  if (begin == end) {
    finish();
    return result;
  }

  {
    std::unique_lock<std::mutex> lock{queue_mutex_};
    for (auto iterator = begin; iterator != end; ++iterator) {
      auto wrapped_task = 
      [shared_task, finish_loop, shared_counter, iterator, finish]
      (const int /* thread_number */)
      {
        (*shared_task)(iterator);
        const int count = --(*shared_counter);
        if (count == 0)
          finish();
      };
      task_queue_.emplace(wrapped_task);
    }
  }
  condition_.notify_all();

  return result;
}

/*!
  \details
  No detailed.
  */
template <typename Integer>
std::future<void> ThreadPool::loop(std::function<void (int, Integer)>&& task, 
                                   Integer begin, 
                                   Integer end)
{
  static_assert(std::is_integral<Integer>::value,
                "## Integer must be integer type.");

  auto shared_task = new std::function<void(int, Integer)>{std::move(task)};
  auto finish_loop = new std::packaged_task<void ()>{[](){}};
  const int distance = cast<int>(end - begin);
  auto shared_counter = new std::atomic_int{distance};

  auto finish = [shared_task, finish_loop, shared_counter]()
  {
    (*finish_loop)();
    delete shared_counter;
    delete finish_loop;
    delete shared_task;
  };

  auto result = finish_loop->get_future();

  if (begin == end) {
    finish();
    return result;
  }

  {
    std::unique_lock<std::mutex> lock{queue_mutex_};
    for (auto iterator = begin; iterator != end; ++iterator) {
      auto wrapped_task = 
      [shared_task, finish_loop, shared_counter, iterator, finish]
      (const int thread_number)
      {
        (*shared_task)(thread_number, iterator);
        const int count = --(*shared_counter);
        if (count == 0)
          finish();
      };
      task_queue_.emplace(wrapped_task);
    }
  }
  condition_.notify_all();

  return result;
}

/*!
  \details
  No detailed.

  \return The number of worker threads
  */
inline
std::size_t ThreadPool::numOfThreads() const
{
  return workers_.size();
}

} // namespace zisc

#endif // _ZISC_THREAD_POOL_INL_HPP_
