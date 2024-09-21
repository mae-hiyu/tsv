/*!
  \file string.hpp
  \author takemura
  */

#ifndef _REFLECT_STRING_HPP_
#define _REFLECT_STRING_HPP_

// Qt
#include <QString>

namespace reflect {

//! \addtogroup Utility
//! \{

//! Convert to QString
template <typename Type>
QString toQString(const Type& message);

//! Convert to QString 
template <typename Type, typename ...Types>
QString toQString(const Type& message, const Types& ...messages);

//! \} Utility

} // namespace reflect

#include "string-inl.hpp"

#endif // _REFLECT_STRING_HPP_
