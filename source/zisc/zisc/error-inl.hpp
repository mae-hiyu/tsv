/*!
 \file error-inl.hpp"
 \author takemura
 */

#ifndef _ZISC_ERROR_INL_HPP_
#define _ZISC_ERROR_INL_HPP_

#include "error.hpp"
// 標準C++ライブラリ
#include <cstdlib>
#include <iostream>

namespace zisc {

namespace inner {

/*!
 \brief エラーメッセージを出力します
 \details
 No detailed.

 \param[in] error_message エラーメッセージ
 */
template <typename Type> inline
void outputErrorMessage(const Type& error_message)
{
  std::cerr << error_message;
}

/*!
 \brief エラーメッセージを出力します
 \details
 No detailed.

 \param[in] error_message エラーメッセージ
 \param[in] error_messages エラーメッセージ
 */
template <typename Type, typename ...Types> inline
void outputErrorMessage(const Type& error_message, const Types&... error_messages)
{
  outputErrorMessage(error_message);
  outputErrorMessage(error_messages...);
}

} // namespace inner

/*!
 \details
 No detailed.

 \param[in] error_messages エラーメッセージ
 */
template <typename ...Types>
void raiseError(const Types&... error_messages)
{
  inner::outputErrorMessage("## ERROR: ", error_messages..., "\n");
  std::exit(EXIT_FAILURE);
}

} // namespace zisc

#endif // _ZISC_ERROR_INL_HPP_
