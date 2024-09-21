/*!
 \file progress_bar.hpp
 \author takemura
 */

#ifndef _ZISC_PROGRESS_BAR_HPP_
#define _ZISC_PROGRESS_BAR_HPP_

// 標準C++ライブラリ
#include <cstddef>
#include <cstdint>
#include <vector>
// Ziscライブラリ
#include "non_copyable.hpp"

namespace zisc {

/*!
 \brief プログレスバーを表示します。
 \details
 No detailed.
 */
class ProgressBar : public NonCopyable
{
 public:  
  using count_type = double;


  ProgressBar();


  //! カウンタの値を進めます
  template <typename ...Types>
  void count(const Types& ...messages);

  //! プログレスバーとメッセージを表示します
  template <typename ...Types>
  void print(const Types& ...messages);

  //! カウンタをリセットします
  void reset();

  //! プログレスバーの設定を行います
  void setProgressBar(const std::size_t max, const std::size_t num_of_bar);

 private:
  //! メッセージを出力します
  template <typename Type, typename ...Types>
  void printMessage(const Type& message, const Types& ...messages) const;

  //! メッセージを出力します
  template <typename Type>
  void printMessage(const Type& message) const;

  //! 何も表示しません
  void printMessage() const {}

  //! プログレスバーを表示します
  void printProgressBar();

  //
  void progress();
  

  bool is_progressed_;
  std::size_t progress_;
  count_type count_;
  std::vector<count_type> border_list_;
};

} // namespace zisc

#include "progress_bar-inl.hpp"

#endif // _ZISC_PROGRESS_BAR_HPP_
