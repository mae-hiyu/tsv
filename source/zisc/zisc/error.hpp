/*!
 \file error.hpp
 \author takemura
 */

#ifndef _ZISC_ERROR_HPP_
#define _ZISC_ERROR_HPP_

namespace zisc {

//! エラーを出力し、プログラムを終了します
template <typename ...Types>
void raiseError(const Types&... error_messages);

} // namespace zisc

#include "error-inl.hpp"

#endif // _ZISC_ERROR_HPP_
