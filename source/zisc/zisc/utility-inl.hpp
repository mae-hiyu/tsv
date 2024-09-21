/*!
  \file utility-inl.hpp
  \author takemura
  */

#ifndef _ZISC_UTILITY_INL_HPP_
#define _ZISC_UTILITY_INL_HPP_

#include "utility.hpp"
// 標準C++ライブラリ
#include <cstdint>
#include <type_traits>

namespace zisc {

/*!
  \brief 型変換を行います
  \details
  No detailed.

  \param[in] value 変換する値
  \tparam Type 変換後の型
  \tparam T 変換前の型
  \return 変換後の値
  */
template <typename Type, typename T> inline
constexpr Type cast(const T value)
{
  return static_cast<Type>(value);
}

/*!
 \brief 範囲内に値を収めます
 \details
 No detailed.

 \param[in] min 最小値
 \param[in] max 最大値
 \param[in] x 判定する値
 \return 圧縮された値
*/
template <typename Arithmetic> inline
constexpr Arithmetic clamp(const Arithmetic min, 
                           const Arithmetic max, 
                           const Arithmetic x)
{
  static_assert(std::is_arithmetic<Arithmetic>::value, "## Must be arithmetic type.");
  return (x < min)
    ? min
    : (max < x)
      ? max
      : x;
}

/*!
  \details
  No detailed.

  \return 符号ビット
  */
template <> inline
constexpr std::int8_t getSignedBit<std::int8_t>()
{
  return static_cast<std::int8_t>(0x80);
}

/*!
  \details
  No detailed.

  \return 符号ビット
  */
template <> inline
constexpr std::int16_t getSignedBit<std::int16_t>()
{
  return static_cast<std::int16_t>(0x8000);
}

/*!
  \details
  No detailed.

  \return 符号ビット
  */
template <> inline
constexpr std::int32_t getSignedBit<std::int32_t>()
{
  return static_cast<std::int32_t>(0x80000000);
}

/*!
  \details
  No detailed.

  \return 符号ビット
  */
template <> inline
constexpr std::int64_t getSignedBit<std::int64_t>()
{
  return static_cast<std::int64_t>(0x8000000000000000);
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
constexpr Type getSignedBit()
{
  static_assert(std::is_integral<Type>::value && std::is_signed<Type>::value,
                "## Template must be signed integer type.");
  return static_cast<Type>(0);
}

/*!
  \details
  No detailed.
  */
template <typename Type, typename T> inline
constexpr Type treatAs(const T* object)
{
  return static_cast<Type>(static_cast<const void*>(object));
}

/*!
  \details
  No detailed.
  */
template <typename Type, typename T> inline
constexpr Type treatAs(T* object)
{
  return static_cast<Type>(static_cast<void*>(object));
}

} // namespace zisc

#endif // _ZISC_UTILITY_INL_HPP_
