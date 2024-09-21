/*!
  \file aligned_memory_pool-inl.hpp
  \author takemura
  */

#ifndef _ZISC_ALIGNED_MEMORY_POOL_INL_HPP_
#define _ZISC_ALIGNED_MEMORY_POOL_INL_HPP_

#include "aligned_memory_pool.hpp"
// Standard C++ library
#include <cstddef>
#include <type_traits>
#include <utility>
// Zisc
#include "error.hpp"
#include "non_copyable.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <std::size_t kSize, std::size_t kAlignment> inline
AlignedMemoryPool<kSize, kAlignment>::AlignedMemoryPool() :
    index_{0}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSize, std::size_t kAlignment> inline
AlignedMemoryPool<kSize, kAlignment>::AlignedMemoryPool(
    AlignedMemoryPool&& memory_pool) :
        index_{memory_pool.index_}
{
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSize, std::size_t kAlignment> 
template <typename Type, typename ...Arguments> inline
Type* AlignedMemoryPool<kSize, kAlignment>::allocate(Arguments&& ...arguments)
{
//  static_assert(kAlignment == std::alignment_of<Type>::value,
//                "## Type alignment doesn't match memory alignment.");

  void* position = static_cast<void*>(&memory_[index_]);

  constexpr std::size_t length = (sizeof(Type) % kAlignment) == 0
      ? sizeof(Type) / kAlignment
      : sizeof(Type) / kAlignment + 1;
  index_ += length;

  if (kLength < index_)
    raiseError("AlignedMemoryPoolError: Memory overflow.");

  return new(position) Type{std::forward<Arguments>(arguments)...};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSize, std::size_t kAlignment> inline
void AlignedMemoryPool<kSize, kAlignment>::reset()
{
  index_ = 0;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSize, std::size_t kAlignment> inline
std::size_t AlignedMemoryPool<kSize, kAlignment>::usedMemory() const
{
  return index_ * kAlignment;
}

} // namespace zisc

#endif // _ZISC_ALIGNED_MEMORY_POOL_INL_HPP_
