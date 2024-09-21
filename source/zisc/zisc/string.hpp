/*!
 \file string.hpp
 \author takemura
 */

#ifndef _ZISC_STRING_HPP_
#define _ZISC_STRING_HPP_

// Standard C++ library
#include <string>

namespace zisc {

//! Convert string to boolean
bool toBoolean(const std::string& string);

//! Convert string to floating point
template <typename Float>
Float toFloat(const std::string& string);

//! Convert string to integer
template <typename Integer> 
Integer toInteger(const std::string& string);

//! Determine if a string is an boolean
bool isBooleanString(const std::string& string);

//! Determine if a string is a floating point
bool isFloatString(const std::string& string);

//! Determine if a string is an integer
bool isIntegerString(const std::string& string);

//! Determine if a string is an unsigned integer
bool isUnsignedIntegerString(const std::string& string);

//! Load text taking account of EOL from file
std::string load(const std::string& file_path);

//! Removes all spaces from the beginning and end of the supplied string.
std::string trim(const std::string& string);

} // namespace zisc

#include "string-inl.hpp"

#endif // _ZISC_STRING_HPP_
