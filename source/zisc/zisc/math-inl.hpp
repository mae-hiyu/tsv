/*!
 \file math-inl.h
 \author takemura
 */

#ifndef _ZISC_MATH_INL_HPP_
#define _ZISC_MATH_INL_HPP_

#include "math.hpp"
// Standard C++ library
#include <cmath>
#include <cstdint>
#include <type_traits>
// Zisc
#include "utility.hpp"

namespace zisc {

/*!
 \details
 No detailed.

 \param[in] n 符号付きの値
 \return nの絶対値
 */
template <typename Signed> inline
constexpr Signed abs(const Signed n)
{
  static_assert(std::is_signed<Signed>::value, "## n must be signed type");
  return isNegative(n)
    ? -n
    : n;
}

/*!
 \details
 ユークリッドの互除法を用います

 \param[in] m 自然数
 \param[in] n 自然数
 \return mとnの最大公約数
 */
template <typename Integer> inline
constexpr Integer gcd(const Integer m, const Integer n)
{
  static_assert(std::is_integral<Integer>::value, "## m, n must be integer type.");
  return m < n
    ? gcd(n, m)
    : n == cast<Integer>(0)
      ? m
      : gcd(n, m % n);
}

/*!
 \details
 No detailed.

 \param[in] n 算術値
 \returh nが負ならばtrue、そうでなければfalse
 */
template <typename Signed> inline
constexpr bool isNegative(const Signed n)
{
  static_assert(std::is_signed<Signed>::value, "## n must be signed type.");
  return n < static_cast<Signed>(0);
}

/*!
 \details
 No detailed.

 \param[in] n 算術値
 \returh nが負ならばtrue、そうでなければfalse
 */
template <> inline
constexpr bool isNegative<std::int8_t>(const std::int8_t n)
{
  return (n & getSignedBit<std::int8_t>()) == getSignedBit<std::int8_t>();
}

template <> inline
constexpr bool isNegative<std::int16_t>(const std::int16_t n)
{
  return (n & getSignedBit<std::int16_t>()) == getSignedBit<std::int16_t>();
}

template <> inline
constexpr bool isNegative<std::int32_t>(const std::int32_t n)
{
  return (n & getSignedBit<std::int32_t>()) == getSignedBit<std::int32_t>();
}

template <> inline
constexpr bool isNegative<std::int64_t>(const std::int64_t n)
{
  return (n & getSignedBit<std::int64_t>()) == getSignedBit<std::int64_t>();
}

/*!
  \details
  No detailed.
  */
template <std::size_t kExponent, typename Arithmetic> inline
constexpr Arithmetic power(const Arithmetic x)
{
  static_assert(std::is_arithmetic<Arithmetic>::value,"## x must be arithmetic type");
  return (kExponent == 0)
    ? cast<Arithmetic>(1)
    : (kExponent == 1)
      ? x
      : ((kExponent & 1) == 1)
        ? x * power<(kExponent >> 1)>(x) * power<(kExponent >> 1)>(x)
        : power<(kExponent >> 1)>(x) * power<(kExponent >> 1)>(x);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic>
Arithmetic power(Arithmetic x, int exponent)
{
  static_assert(std::is_arithmetic<Arithmetic>::value,"## x must be arithmetic type");
  if (isNegative(exponent)) {
    x = cast<Arithmetic>(1) / x;
    exponent = -exponent;
  }
  Arithmetic result = cast<Arithmetic>(1);
  while (exponent) {
    if ((exponent & 1) == 1)
      result = result * x;
    x = x * x;
    exponent = exponent >> 1;
  }
  return result;
}

/*!
  \details
  No detailed.
  */
inline
float invSqrt(const float n)
{
  return 1.0f / zisc::sqrt(n);
}

/*!
  \details
  No detailed.
  */
inline
double invSqrt(const double n)
{
  return 1.0 / zisc::sqrt(n);
}

/*!
  \details
  No detailed.
  */
inline
float sqrt(const float n)
{
  return std::sqrt(n);
}

/*!
  \details
  No detailed.
  */
inline
double sqrt(const double n)
{
  return std::sqrt(n);
}

/*!
  \details
  No detailed.
  */
inline
float cos(const float theta)
{
  return std::cos(theta);
}

/*!
  \details
  No detailed.
  */
inline
double cos(const double theta)
{
  return std::cos(theta);
}

/*!
  \details
  No detailed.
  */
inline
float sin(const float theta)
{
  return std::sin(theta);
}

/*!
  \details
  No detailed.
  */
inline
double sin(const double theta)
{
  return std::sin(theta);
}

/*!
  \details
  No detailed.
  */
inline
float arcCos(const float x)
{
  return std::acos(x);
}

/*!
  \details
  No detailed.
  */
inline
double arcCos(const double x)
{
  return std::acos(x);
}

/*!
  \details
  No detailed.
  */
inline
float arcSin(const float x)
{
  return std::asin(x);
}

/*!
  \details
  No detailed.
  */
inline
double arcSin(const double x)
{
  return std::asin(x);
}

namespace approx {

/*!
 \details
 No detailed.

 \param[in] n 平方根の逆数を求める数
 \return n の平方根の逆数
 */
inline
float invSqrt(const float n)
{
  constexpr std::int32_t kMagicNumber = 0x5f3759df;
  union {float f; std::int32_t i;} u{n};
  u.i = kMagicNumber - (u.i >> 1);
  u.f = u.f * (1.5f - 0.5f * n * u.f * u.f);
  return u.f * (1.5f - 0.5f * n * u.f * u.f);
}

/*!
 \details
 No detailed.

 \param[in] n 平方根の逆数を求める数
 \return n の平方根の逆数
 */
inline
double invSqrt(const double n)
{
  constexpr std::int64_t kMagicNumber = 0x5fe6eb50c7b537aaLL;
  union {double f; std::int64_t i;} u{n};
  u.i = kMagicNumber - (u.i >> 1);
  u.f = u.f * (1.5 - 0.5 * n * u.f * u.f);
  return u.f * (1.5 - 0.5 * n * u.f * u.f);
}

/*!
 \details
 No detailed.

 \param[in] n 平方根を求める数
 \return n の平方根
 */
inline
float sqrt(const float n)
{
  return n * invSqrt(n);
}

/*!
 \details
 No detailed.

 \param[in] n 平方根を求める数
 \return n の平方根
 */
inline
double sqrt(const double n)
{
  return n * invSqrt(n);
}

// Trigonometric functions

/*!
 \details
 アルゴリズムの詳細はhttp://lab.polygonal.de/?p=205を参照して下さい。

 \attention theta は -pi <= theta < pi でなければなりません

 \tparam Float 浮動小数点型
 \tparam high_precision trueの場合、高精度な近似値を求めます

 \param[in] theta ラジアン
 \return cos(theta)の値
 */
template <typename Float, bool high_precision> inline
constexpr Float cos(const Float theta)
{
  static_assert(std::is_floating_point<Float>::value, "## theta must be float type.");
  return theta > cast<Float>(kPi * 0.5)
    ? sin<Float, high_precision>(theta - cast<Float>(kPi * 1.5))
    : sin<Float, high_precision>(theta + cast<Float>(kPi * 0.5));
}

/*!
 \details
 アルゴリズムの詳細はhttp://lab.polygonal.de/?p=205を参照して下さい。

 \attention theta は -pi <= theta < pi でなければなりません

 \tparam Float 浮動小数点型
 \tparam high_precision trueの場合、高精度な近似値を求めます

 \param[in] theta ラジアン
 \return sin(theta)の値
 */
template <typename Float, bool high_precision> inline
constexpr Float sin(const Float theta)
{
  static_assert(std::is_floating_point<Float>::value, "## theta must be float type.");
  return high_precision
    ? sin<Float, false>(theta) * (isNegative(sin<Float, false>(theta))
      ? cast<Float>(0.775) - cast<Float>(0.225) * sin<Float, false>(theta)
      : cast<Float>(0.775) + cast<Float>(0.225) * sin<Float, false>(theta))
    : theta * (isNegative(theta)
      ? cast<Float>(1.2732395447) + cast<Float>(0.4052847346) * theta
      : cast<Float>(1.2732395447) - cast<Float>(0.4052847346) * theta);
}

/*!
  \details
  No detailed.

  \param[in] x 
  \return radian

  \attention 有効なxの範囲は [-1, 1] です
  */
template <typename Float> inline
/* constexpr */ Float arcCos(const Float x)
{
  static_assert(std::is_floating_point<Float>::value, "## x must be float type.");
  return x < cast<Float>(0.0)
    ? cast<Float>(kPi) - cast<Float>(2.0) *
      arcTan((cast<Float>(1.0) + x) * invSqrt(cast<Float>(1.0) - x * x))
    : cast<Float>(2.0) * 
      arcTan((cast<Float>(1.0) - x) * invSqrt(cast<Float>(1.0) - x * x));
}

/*!
  \details
  No detailed.

  \param[in] x 
  \return radian

  \attention 有効なxの範囲は [-1, 1] です
  */
template <typename Float> inline
/* constexpr */ Float arcSin(const Float x)
{
  static_assert(std::is_floating_point<Float>::value, "## x must be float type.");
  return cast<Float>(kPi * 0.5) - arcCos(x);
}

/*!
  \details
  このアルゴリズムの詳細は "http://nghiaho.com/?p=997" を参照して下さい.

  \param[in] x 
  \return radian

  \attention 有効なxの範囲は [-1, 1] です
  */
template <typename Float> inline
constexpr Float arcTan(const Float x)
{
  static_assert(std::is_floating_point<Float>::value, "## x must be float type.");
  return x * (cast<Float>(kPi * 0.25) - (isNegative(x)
    ? (-cast<Float>(1.0) - x) * (cast<Float>(0.2447) - cast<Float>(0.0663) * x)
    : (-cast<Float>(1.0) + x) * (cast<Float>(0.2447) + cast<Float>(0.0663) * x)));
}

/*!
  \details
  No detailed.

  \param[in] x 
  */
inline
float log2(const float x)
{
  union {float f; std::uint32_t i;} const vx{x};
  union {std::uint32_t i; float f;} const mx{(vx.i & 0x007FFFFF) | 0x3f000000};
  const float y = cast<float>(vx.i) * 1.1920928955078125e-7f;
  return y - 124.22551499f - 1.498030302f * mx.f - 1.72587999f / (0.3520887068f+mx.f);
}

inline 
float log(const float x)
{
  return 0.69314718f * log2(x);
}

} // namespace approx

/*!
  \details
  No detailed.
  */
template <typename Type> inline
constexpr const Type& max(const Type& a, const Type& b)
{
  return (a > b) ? a : b;
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
constexpr const Type& min(const Type& a, const Type& b)
{
  return (a < b) ? a : b;
}

/*!
  \details
  No detailed.
  */
template <typename Float> inline
void solveCubicEquation(const Float a, const Float b,
                        const Float c, const Float d,
                        std::size_t* n, Float* x)
{
  static_assert(std::is_floating_point<Float>::value,
                "## Float must be floating point type.");

  constexpr Float t0 = 1.0 / 3.0;
  const Float t1 = t0 / a;

  const Float q = (3.0 * a * c - b * b) * (t1 * t1);
  const Float r = (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b) *
                  (t1 * t1 * t1 * 0.5);
  const Float discriminant = q * q * q + r * r;

  if (discriminant > 0.0) {
    const Float s = std::cbrt(r + std::sqrt(discriminant));
    const Float t = std::cbrt(r - std::sqrt(discriminant));
    *n = 1;
    x[0] = s + t - (b * t1);
  }
  else if (discriminant == 0.0) {
    const Float s = std::cbrt(r + std::sqrt(discriminant));
    const Float t = std::cbrt(r - std::sqrt(discriminant));
    const Float x1 = s + t - (b * t1);
    const Float x2 = -0.5 * (s + t) - (b * t1);
    if (x1 == x2) {
      *n = 1;
      x[0] = x1;
    }
    else {
      *n = 2;
      x[0] = x1;
      x[1] = x2;
    }
  }
  else {
    const Float cos_theta = r / std::sqrt(-q * q * q);
    const Float theta = std::acos(cos_theta);
    constexpr Float phi1 = 2.0 * kPi / 3.0;
    constexpr Float phi2 = 4.0 * kPi / 3.0;

    *n = 3;
    x[0] = 2.0 * std::sqrt(-q) * std::cos(theta * t0) - (b * t1);
    x[1] = 2.0 * std::sqrt(-q) * std::cos(theta * t0 + phi1) - (b * t1);
    x[2] = 2.0 * std::sqrt(-q) * std::cos(theta * t0 + phi2) - (b * t1);
  }
}

/*!
  \details
  No detailed.
  */
template <typename Float> inline
void solveQuarticEquation(const Float a1, const Float a2, const Float a3,
                          const Float a4, const Float a5,
                          std::size_t* n, Float* x)
{
  const Float t1 = 1.0 / a1;
  const Float b = a2 * t1,
              c = a3 * t1,
              d = a4 * t1,
              e = a5 * t1;

  constexpr Float t2 = 1.0 / 8.0;
  const Float p = (8.0 * c - 3.0 * b * b) * t2,
              q = (b * b * b - 4.0 * b * c + 8.0 * d) * t2;

  const Float delta0 = c * c - 3.0 * b * d + 12.0 * e,
              delta1 = 2.0 * c * c * c - 9.0 * b * c * d + 
                       27.0 * (b * b * e + d * d) - 72.0 * c * e;

  const Float t3 = delta0 * delta0 * delta0;
  const Float discriminant = delta1 * delta1 - 4.0 * t3;

  Float s;
  constexpr Float t4 = 2.0 / 3.0;
  constexpr Float t5 = 1.0 / 3.0;
  if (discriminant < 0.0) {
    const Float phi = std::acos(delta1 / (2.0 * std::sqrt(t3)));
    s = 0.5 * std::sqrt((std::sqrt(delta0) * std::cos(phi * t5) - p) * t4);
  }
  else {
    const Float t = std::cbrt((delta1 + std::sqrt(discriminant)) * 0.5);
    s = 0.5 * std::sqrt(-t4 * p + t5 * (t + delta0 / t));
  }

  constexpr Float t6 = -1.0 / 4.0;
  const Float x1 = b * t6;
  const Float x2 = -4.0 * s * s - 2.0 * p;
  const Float x3 = q / s;

  std::size_t index = 0;
  if ((x2 + x3) > 0.0) {
    const Float t7 = 0.5 * std::sqrt(x2 + x3);
    x[index    ] = x1 - s + t7;
    x[index + 1] = x1 - s - t7;
    index = index + 2;
  }
  if ((x2 - x3) > 0.0) {
    const Float t7 = 0.5 * std::sqrt(x2 - x3);
    x[index    ] = x1 + s + t7;
    x[index + 1] = x1 + s - t7;
    index = index + 2;
  }
  *n = index;
}

} // namespace zisc

#endif // _ZISC_MATH_INL_HPP_
