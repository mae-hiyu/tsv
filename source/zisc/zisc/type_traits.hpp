/*!
  \file type_traits.hpp
  \author takemura
  */

#ifndef _ZISC_TYPE_TRAITS_HPP_
#define _ZISC_TYPE_TRAITS_HPP_

// 標準C++ライブラリ
#include <string>
#include <type_traits>

namespace zisc {

//! 指定した型が論理型か判定します
template <typename Type>
using IsBoolean = std::is_same<bool, typename std::remove_cv<Type>::type>;

//! 指定した型が浮動小数点か判定します
template <typename Type>
using IsFloat = std::is_floating_point<typename std::remove_cv<Type>::type>;

//! 指定した型が整数型か判定します
template <typename Type>
class IsInteger
{
  using Type_ = typename std::remove_cv<Type>::type;
 public:
  static constexpr bool value = std::is_integral<Type_>::value && 
                                !std::is_same<bool, Type_>::value;
};

//! 指定した型が符号無し整数型か判定します
template <typename Type>
class IsUnsignedInteger
{
  using Type_ = typename std::remove_cv<Type>::type;
 public:
  static constexpr bool value = IsInteger<Type>::value &&
                                std::is_unsigned<Type_>::value;
};

//! 指定した型が符号付き整数型か判定します
template <typename Type>
struct IsSignedInteger
{
  static constexpr bool value = IsInteger<Type>::value &&
                                !IsUnsignedInteger<Type>::value;
};

//! 指定した型が文字列型か判定します
template <typename Type>
class IsString
{
  using Type_ = typename std::remove_cv<Type>::type;
 public:
  static constexpr bool value = std::is_same<std::string, Type_>::value ||
                                std::is_same<const char*, Type_>::value;
};

extern void* kEnabler;

template <typename T, typename Type = void*&>
using EnableIfBoolean = typename std::enable_if<IsBoolean<T>::value, Type>::type;

template <typename T, typename Type = void*&>
using EnableIfFloat = typename std::enable_if<IsFloat<T>::value, Type>::type;

template <typename T, typename Type = void*&>
using EnableIfInteger = typename std::enable_if<IsInteger<T>::value, Type>::type;

template <typename T, typename Type = void*&>
using EnableIfUnsignedInteger = 
    typename std::enable_if<IsUnsignedInteger<T>::value, Type>::type;

template <typename T, typename Type = void*&>
using EnableIfSignedInteger = 
    typename std::enable_if<IsSignedInteger<T>::value, Type>::type;

template <typename T, typename U, typename Type = void*&>
using EnableIfSame = typename std::enable_if<std::is_same<T, U>::value, Type>::type;

template <typename B, typename D, typename Type = void*&>
using EnableIfBaseOf = typename std::enable_if<std::is_base_of<B, D>::value, Type>::type;

template <typename T, typename Type = void*&>
using EnableIfString = typename std::enable_if<IsString<T>::value, Type>::type;

} // namespace zisc

#endif // _ZISC_TYPE_TRAITS_HPP_
