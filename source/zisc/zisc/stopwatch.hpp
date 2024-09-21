/*!
 \file stopwatch.hpp
 \author takemura
 */

#ifndef _ZISC_STOPWATCH_HPP_
#define _ZISC_STOPWATCH_HPP_

// Standard C++ library
#include <chrono>
#include <cstdint>
// Zisc
#include "non_copyable.hpp"

namespace zisc {

/*!
 \brief Measure elapsed processor time
 \details
 No detailed.
 */
class Stopwatch : public NonCopyable
{
 public:
  //! Clock type
  using Clock = std::chrono::high_resolution_clock;


  //! Initialize
  Stopwatch();


  //! Get elapsed milli time
  std::int64_t elapsedTime() const;

  //! Start to measure the time
  void start();

 private:
  Clock::time_point start_time_;
};

/*!
  \details
  No detailed.
  */
template <std::int64_t kPerUnit>
struct Time
{
  //! Get time
  static std::int64_t time(const std::int64_t milli, std::int64_t* rest_milli);
};

using Hour = Time<1000 * 60 * 60>;
using Minute = Time<1000 * 60>;
using Second = Time<1000>;

} // namespace zisc

#include "stopwatch-inl.hpp"

#endif // _ZISC_STOPWATCH_HPP_
