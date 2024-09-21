/*!
 \file progress_bar-inl.hpp
 \author takemura
 */

#include "progress_bar.hpp"
// 標準C++ライブラリ
#include <cstdint>
#include <iostream>

#ifndef _ZISC_PROGRESS_BAR_INL_HPP_
#define _ZISC_PROGRESS_BAR_INL_HPP_

namespace zisc {

// public member function

inline
void ProgressBar::reset()
{
  is_progressed_ = true;
  progress_ = 0u;
  count_ = 0.0;
}

/*!
 \details
 No detailed.

 \param[in] message メッセージ
 */
template <typename ...Types> inline
void ProgressBar::count(const Types& ...messages)
{
  progress();
  if (is_progressed_) {
    print(messages...);
    is_progressed_ = false;
  }
}

/*!
 \details
 No detailed.

 \param[in] message メッセージ
 */
template <typename ...Types> inline
void ProgressBar::print(const Types& ...messages)
{
  printMessage("\r");
  std::cout << std::flush;
  printProgressBar();
  printMessage(messages...);
}

// private member function

/*!
  \details
  No detailed.

  \param[in] message メッセージ
  \param[in] messages メッセージ
  */
template <typename Type, typename ...Types> inline
void ProgressBar::printMessage(const Type& message, const Types& ...messages) const
{
  printMessage(message);
  printMessage(messages...);
}


/*!
  \details
  No detailed.

  \param[in] message メッセージ
  */
template <typename Type> inline
void ProgressBar::printMessage(const Type& message) const
{
  std::cout << message;
}

} // namespace zisc

#endif // _ZISC_PROGRESS_BAR_INL_HPP_
