/*!
  \file renderer_system.hpp
  \author takemura
  */

#ifndef _REFLECT_RENDERER_SYSTEM_HPP_
#define _REFLECT_RENDERER_SYSTEM_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/thread_pool.hpp"
// Reflect
#include "reflect_config.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;

namespace reflect {

//! \addtogroup RendererBase
//! \{

/*!
  \details
  No detailed.
  */
class RendererSystem
{
 public:
  //! Create system
  RendererSystem(const QSettings& settings);


  //! Return the global memory pool
  MemoryPool& globalMemoryPool();

  //! Return the global sampler 
  Sampler& globalSampler();

  //! Initialize
  void initialize(const QSettings& settings);

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the thread pool
  zisc::ThreadPool& threadPool();

  //! Return the thread's memory pool
  MemoryPool& threadMemoryPool(const std::size_t thread_number);

  //! Return the thread's sampler
  Sampler& threadSampler(const std::size_t thread_number);

 private:
  UniquePointer<zisc::ThreadPool> thread_pool_;
  std::vector<Sampler> sampler_list_;
  std::vector<MemoryPool> memory_pool_list_;
};

//! \} RendererBase

} // namespace reflect

#include "renderer_system-inl.hpp"

#endif // _REFLECT_RENDERER_SYSTEM_HPP_
