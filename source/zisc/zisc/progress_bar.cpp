/*!
 \file progress_bar.cpp
 \author takemura
 */

#include "progress_bar.hpp"
// 標準C++ライブラリ
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>
// Ziscライブラリ
#include "utility.hpp"

namespace zisc {

ProgressBar::ProgressBar() : 
    is_progressed_{true},
    progress_{0u},
    count_{0.0}
{
}

/*!
  \details
  No detailed.

  \param[in] max カウンタの最大値
  \param[in] num_of_bar プログレスバーの数
  */
void ProgressBar::setProgressBar(const std::size_t max, const std::size_t num_of_bar)
{
  count_type border = 0.0;
  border_list_.resize(num_of_bar, border);
  for (std::size_t i = 0u; i < num_of_bar; ++i) {
    border += cast<double>(max) / cast<double>(num_of_bar);
    border_list_[i] = border;
  }
  border_list_.back() = cast<double>(max);
  reset();
}

// private member function

/*!
 \details
 No detailed.
 */
void ProgressBar::printProgressBar()
{
  std::cout << "## [";
  for (std::size_t i = 0u; i < progress_; ++i)
    std::cout << "=";
  for (std::size_t i = progress_; i < border_list_.size(); ++i)
    std::cout << " ";
  std::cout << "]";
}

/*!
  \details
  No detailed.
  */
void ProgressBar::progress()
{
  ++count_;
  while (progress_ != border_list_.size() && border_list_[progress_] <= count_) {
    is_progressed_ = true;
    ++progress_;
  }
}


} // namespace zisc
