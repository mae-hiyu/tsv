/*!
  \file renderer_system.cpp
  \author takemura
  */

#include "renderer_system.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/algorithm.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/size.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
RendererSystem::RendererSystem(const QSettings& settings)
{
  initialize(settings);
}

/*!
  \details
  No detailed.
  */
void RendererSystem::initialize(const QSettings& settings)
{
  // Thread pool
  auto key = QString{keyword::system_group} + "/" + keyword::num_of_threads;
  const std::size_t num_of_threads = value<std::size_t>(settings, key);
  thread_pool_ = new zisc::ThreadPool{num_of_threads};

  // Random generator
  key = QString{keyword::system_group} + "/" + keyword::random_seed;
  auto random_seed = value<std::uint32_t>(settings, key);
  sampler_list_.resize(thread_pool_->numOfThreads() + 1);
  for (auto& sampler : sampler_list_) {
    sampler.setSeed(random_seed);
    ++random_seed;
  }

  // Memory pool
  memory_pool_list_.resize(thread_pool_->numOfThreads() + 1);
}

/*!
  \details
  No detailed.
  */
std::size_t RendererSystem::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(thread_pool_);
  size += PRINT_VARIABLE_DATA(sampler_list_);
  size += PRINT_VARIABLE_DATA(memory_pool_list_);
  return size;
}

} // namespace reflect
