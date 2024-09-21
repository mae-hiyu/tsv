/*
 \file matrix-inl.h
 \author takemura
 */

#ifndef _ZISC_MATRIX_INL_H_
#define _ZISC_MATRIX_INL_H_

#include "matrix.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
// Zisc
#include "arithmetic_array.hpp"
#include "point.hpp"
#include "utility.hpp"
#include "vector.hpp"

namespace zisc {

// public member function

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Matrix<Arithmetic, kRow, kColumn>::Matrix()
{
}

/*!
 \details
 No detailed.
 */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn>
template <typename ...Types> inline
Matrix<Arithmetic, kRow, kColumn>::Matrix(const Types ...elements) :
    elements_{elements...}
{
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
bool Matrix<Arithmetic, kRow, kColumn>::operator==(const Matrix& matrix) const
{
  return elements_ == matrix.elements_;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
bool Matrix<Arithmetic, kRow, kColumn>::operator!=(const Matrix& matrix) const
{
  return elements_ != matrix.elements_;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
auto Matrix<Arithmetic, kRow, kColumn>::operator*(const Arithmetic scalar) const
    -> Matrix
{
  Matrix matrix;
  matrix.elements_ = scalar * elements_;
  return matrix;
}

/*!
 \details
 No detailed.
 */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Arithmetic& Matrix<Arithmetic, kRow, kColumn>::operator()(
    const std::size_t row,
    const std::size_t column)
{
  return elements_[row * kColumn + column];
}

/*!
 \details
 No detailed.
 */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
const Arithmetic& Matrix<Arithmetic, kRow, kColumn>::operator()(
    const std::size_t row,
    const std::size_t column) const
{
  return elements_[row * kColumn + column];
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Arithmetic Matrix<Arithmetic, kRow, kColumn>::cofactor(
    const std::size_t row,
    const std::size_t column) const
{
  return (((row + column) & 1) == 1)
      ? -minorDeterminant(row, column)
      : minorDeterminant(row, column);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
auto Matrix<Arithmetic, kRow, kColumn>::cofactorMatrix() const -> Matrix
{
  Matrix cofactor_matrix;
  for (std::size_t row = 0; row < kRow; ++row) {
    for (std::size_t column = 0; column < kColumn; ++column) {
      cofactor_matrix.set(row, column, cofactor(column, row));
    }
  }
  return cofactor_matrix;
}

namespace inner {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Arithmetic calculateDeterminant(const Matrix<Arithmetic, kN, kN>& matrix)
{
  Arithmetic determinant = cast<Arithmetic>(0);
  for (std::size_t column = 0; column < kN; ++column)
    determinant += matrix(0, column) * matrix.cofactor(0, column);
  return determinant;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic> inline
Arithmetic calculateDeterminant(const Matrix<Arithmetic, 2, 2>& matrix)
{
  return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic> inline
Arithmetic calculateDeterminant(const Matrix<Arithmetic, 1, 1>& matrix)
{
  return matrix(0, 0);
}

} // namespace inner

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Arithmetic Matrix<Arithmetic, kRow, kColumn>::determinant() const
{
  static_assert(isSquareMatrix(), "## Matrix must be square matrix.");
  return inner::calculateDeterminant(*this);
}

/*!
 \details
 No detailed.
 */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Arithmetic Matrix<Arithmetic, kRow, kColumn>::get(
    const std::size_t row, 
    const std::size_t column) const
{
  return elements_.get(row * kColumn + column);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
auto Matrix<Arithmetic, kRow, kColumn>::inverseMatrix() const -> Matrix
{
  return (cast<Arithmetic>(1) / determinant()) * cofactorMatrix();
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn>
Arithmetic Matrix<Arithmetic, kRow, kColumn>::minorDeterminant(
    const std::size_t row, const std::size_t column) const
{
  static_assert(isSquareMatrix(), "## Matrix must be square matrix.");
  constexpr std::size_t n = kRow;

  // Make submatrix
  Matrix<Arithmetic, n - 1, n - 1> submatrix;
  std::size_t r = 0,
              c = 0;
  for (std::size_t i = 0; i < kRow; ++i) {
    if (i == row)
      continue;
    for (std::size_t j = 0; j < kColumn; ++j) {
      if (j == column)
        continue;
      submatrix.set(r, c, get(i, j));
      ++c;
    }
    ++r;
    c = 0;
  }

  // Calculate minor determinant
  return submatrix.determinant();
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
void Matrix<Arithmetic, kRow, kColumn>::set(const std::size_t row,
                                            const std::size_t column,
                                            const Arithmetic value)
{
  elements_.set(row * kColumn + column, value);
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Matrix<Arithmetic, kColumn, kRow> Matrix<Arithmetic, kRow, kColumn>::
    transposedMatrix() const
{
  Matrix<Arithmetic, kColumn, kRow> transposed_matrix;
  for (std::size_t row = 0; row < kRow; ++row) {
    for (std::size_t column = 0; column < kColumn; ++column) {
      transposed_matrix.set(column, row, get(row, column));
    }
  }
  return transposed_matrix;
}

/*!
 \details
 No detailed.
 */
template <typename Arithmetic, std::size_t L, std::size_t M, std::size_t N>
Matrix<Arithmetic, L, N> operator*(const Matrix<Arithmetic, L, M>& a,
                                   const Matrix<Arithmetic, M, N>& b)
{
  Matrix<Arithmetic, L, N> matrix{};
  Arithmetic value;
  for (std::size_t l = 0; l < L; ++l) {
    for (std::size_t n = 0; n < N; ++n) {
      value = cast<Arithmetic>(0);
      for (std::size_t m = 0; m < M; ++m)
        value += a(l, m) * b(m, n);
      matrix.set(l, n, value);
    }
  }
  return matrix;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn> inline
Matrix<Arithmetic, kRow, kColumn> operator*(
    const Arithmetic scalar,
    const Matrix<Arithmetic, kRow, kColumn>& matrix)
{
  return matrix * scalar;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> operator*(
    const Matrix<Arithmetic, kN, kN>& matrix,
    const ArithmeticArray<Arithmetic, kN>& array)
{
  ArithmeticArray<Arithmetic, kN> result;
  Arithmetic value;
  for (std::size_t row = 0; row < kN; ++row) {
    value = cast<Arithmetic>(0);
    for (std::size_t column = 0; column < kN; ++column)
      value += matrix(row, column) * array[column];
    result.set(row, value);
  }
  return result;
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Point<Arithmetic, kN> operator*(const Matrix<Arithmetic, kN, kN>& matrix,
                                const Point<Arithmetic, kN>& point)
{
  return matrix * point.data();
}

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kN> inline
Vector<Arithmetic, kN> operator*(const Matrix<Arithmetic, kN, kN>& matrix,
                                 const Vector<Arithmetic, kN>& vector)
{
  return matrix * vector.data();
}

} // namespace zisc

#endif // _ZISC_MATRIX_INL_H_
