/*!
  \file aligned_memory_pool.hpp
  \author takemura
  */

#ifndef _ZISC_ALIGNED_MEMORY_POOL_HPP_
#define _ZISC_ALIGNED_MEMORY_POOL_HPP_

// Standard C++ library
#include <cstddef>
#include <type_traits>
// Zisc
#include "non_copyable.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <std::size_t kSize, std::size_t kAlignment>
class AlignedMemoryPool : public NonCopyable
{
  static constexpr std::size_t kLength = ((kSize % kAlignment) == 0)
      ? kSize / kAlignment
      : kSize / kAlignment + 1;

 public:
  //! Create a memory pool
  AlignedMemoryPool();

  //! Move memory data
  AlignedMemoryPool(AlignedMemoryPool&& memory_pool);


  //! Allocate memory
  template <typename Type, typename ...Arguments>
  Type* allocate(Arguments&& ...arguments);

  //! Reset memory pool
  void reset();

  //! Return the size of memory pool
  static constexpr std::size_t size()
  {
    return kLength * kAlignment;
  }

  //! Return the used memory
  std::size_t usedMemory() const;

 private:
  using AlignedBlock = typename std::aligned_storage<kAlignment, kAlignment>::type;


  AlignedBlock memory_[kLength];
  std::size_t index_;
};

} // namespace zisc

#include "aligned_memory_pool-inl.hpp"

#endif // _ZISC_ALIGNED_MEMORY_POOL_HPP_
