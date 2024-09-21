/*!
 \file stopwatch-inl.hpp
 \author takemura
 */

#include "stopwatch.hpp"
// Standard C++ library
#include <chrono>
#include <cstdint>
// Zisc
#include "utility.hpp"

#ifndef _ZISC_STOPWATCH_INL_HPP_
#define _ZISC_STOPWATCH_INL_HPP_

namespace zisc {

/*!
  \details
  No detailed.
  */
inline
Stopwatch::Stopwatch()
{
}

/*!
  \details
  No detailed.
  */
inline
std::int64_t Stopwatch::elapsedTime() const
{
  const auto current_time = Clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - 
                                                               start_time_).count();
}

/*!
  \details
  No detailed.
  */
inline
void Stopwatch::start()
{
  start_time_ = Clock::now();
}

/*!
  \details
  No detailed.
  */
template <std::int64_t kPerUnit> inline
std::int64_t Time<kPerUnit>::time(const std::int64_t milli, std::int64_t* rest_milli)
{
  const std::int64_t time = milli / kPerUnit;
  if (rest_milli != nullptr)
    *rest_milli = milli - time * kPerUnit;
  return time;
}

} // namespace zisc

#endif // _ZISC_STOPWATCH_INL_HPP_
