/*!
 \file math.hpp
 \author takemura
 */

#ifndef _ZISC_MATH_HPP_
#define _ZISC_MATH_HPP_

// Standard C++ library
#include <cstddef>

namespace zisc {

constexpr double kE = 2.718281828459045235360287471352; //!< ネイピア数
constexpr double kPi = 3.14159265358979323846264338327950288; //!< 円周率

// Basic operations

//! 絶対値を取得します
template <typename Arithmetic>
constexpr Arithmetic abs(const Arithmetic n);

//! 最大公約数を取得します
template <typename Integral>
constexpr Integral gcd(const Integral a, const Integral b);

//! 値の負が確認します
template <typename Signed>
constexpr bool isNegative(const Signed n);

// Power functions

//! Calculate x^(exponent)
template <std::size_t kExponent, typename Arithmetic>
constexpr Arithmetic power(const Arithmetic x);

//! Calculate x^(exponent)
template <typename Arithmetic>
Arithmetic power(Arithmetic x, int exponent);

//! Calculate the inverse square root
float invSqrt(const float n);

//! Calculate the inverse square root
double invSqrt(const double n);

//! Calculate the square root
float sqrt(const float n);

//! Calculate the square root
double sqrt(const double n);

// Trigonometric functions

//! Calculate cos(theta)
float cos(const float theta);

//! Calculate cos(theta)
double cos(const double theta);

//! Calculate sin(theta)
float sin(const float theta);

//! Calculate sin(theta)
double sin(const double theta);

//! Calculate arccos(x)
float arcCos(const float x);

//! Calculate arccos(x)
double arcCos(const double x);

//! Calculate arcsin(x)
float arcSin(const float x);

//! Calculate arcsin(x)
double arcSin(const double x);

// Mininum/Maximum operation

//! Return the large of two elements
template <typename Type>
constexpr const Type& max(const Type& a, const Type& b);

//! Return the small of two elements
template <typename Type>
constexpr const Type& min(const Type& a, const Type& b);

// Approximation functions
namespace approx {

//! 平方根の逆数を求めます
float invSqrt(const float n);

//! 平方根の逆数を求めます
double invSqrt(const double n);

//! 平方根を求めます
float sqrt(const float n);

//! 平方根を求めます
double sqrt(const double n);

// Trigonometric functions

//! cos(x) を求めます
template <typename Float, bool high_precision = true>
constexpr Float cos(const Float theta);

//! sin(x) を求めます
template <typename Float, bool high_precision = true>
constexpr Float sin(const Float theta);

//! arccos(x) を求めます
template <typename Float>
/* constexpr */ Float arcCos(const Float x);

//! arcsin(x) を求めます
template <typename Float>
/* constexpr */ Float arcSin(const Float x);

//! arctan(x) を求めます
template <typename Float>
constexpr Float arcTan(const Float x);

// Polynomial

//! Solve a cubic equation
template <typename Float>
void solveCubicEquation(const Float a, const Float b, 
                        const Float c, const Float d,
                        std::size_t* n, Float* x);


//! Solve a quartic equation
template <typename Float>
void solveQuarticEquation(const Float a1, const Float a2, const Float a3,
                          const Float a4, const Float a5,
                          std::size_t* n, Float* x);

// Log

//! 2を底とするlogを求めます
float log2(const float x);

//! eを底とするlogを求めます
float log(const float x);

} // namespace approx

} // namespace zisc

#include "math-inl.hpp"

#endif // _ZISC_MATH_HPP_
