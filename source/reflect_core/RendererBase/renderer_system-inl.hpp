/*!
  \file renderer_system-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERER_SYSTEM_INL_HPP_
#define _REFLECT_RENDERER_SYSTEM_INL_HPP_

#include "renderer_system.hpp"
// Standard C++ library
#include <vector>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/thread_pool.hpp"
// Reflect
#include "reflect_config.hpp"
#include "Sampling/sampler.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
MemoryPool& RendererSystem::globalMemoryPool()
{
  return memory_pool_list_[0];
}

/*!
  \details
  No detailed.
  */
inline
Sampler& RendererSystem::globalSampler()
{
  return sampler_list_[0];
}

/*!
  \details
  No detailed.
  */
inline
zisc::ThreadPool& RendererSystem::threadPool()
{
  return *thread_pool_;
}

/*!
  \details
  No detailed.
  */
inline
MemoryPool& RendererSystem::threadMemoryPool(const std::size_t thread_number)
{
  return memory_pool_list_[thread_number + 1];
}

/*!
  \details
  No detailed.
  */
inline
Sampler& RendererSystem::threadSampler(const std::size_t thread_number)
{
  return sampler_list_[thread_number + 1];
}

} // namespace reflect

#endif // _REFLECT_RENDERER_SYSTEM_INL_HPP_
