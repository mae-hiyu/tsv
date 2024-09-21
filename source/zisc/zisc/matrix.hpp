/*!
 \file matrix.hpp
 \author takemura
 */

#ifndef _ZISC_MATRIX_HPP_
#define _ZISC_MATRIX_HPP_

// Standard C++ library
#include <cstddef>
#include <type_traits>
// Zisc
#include "arithmetic_array.hpp"
#include "dimension.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace zisc {

/*!
  \details
  No detailed.
  */
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn>
class Matrix
{
  static_assert(kRow > 0, "## kRow size must be greater than 0.");
  static_assert(kColumn > 0, "## kColumn size must be greater than 0.");

 public:
  using ArrayType = ArithmeticArray<Arithmetic, kRow * kColumn>;
  using ValueType = Arithmetic;


  //! Initialize with 0
  Matrix();

  //! Initialize with values
  template <typename ...Types>
  Matrix(const Types ...elements);


  //! Check if two matrixes are same
  bool operator==(const Matrix& matrix) const;

  //! Check if two matrixes are not same
  bool operator!=(const Matrix& matrix) const;

  //! Apply multiplication operation
  Matrix operator*(const Arithmetic scalar) const;

  //! Return the element by row and column
  Arithmetic& operator()(const std::size_t row, const std::size_t column);

  //! Return the element by row and column
  const Arithmetic& operator()(const std::size_t row, const std::size_t column) const;


  //! Calculate the cofactor
  Arithmetic cofactor(const std::size_t row, const std::size_t column) const;

  //! Return the cofactor matrix
  Matrix cofactorMatrix() const;

  //! Return column size
  static constexpr std::size_t columnSize()
  {
    return kColumn;
  }

  //! Calculate the determinant
  Arithmetic determinant() const;

  //! Return the element by row and column
  Arithmetic get(const std::size_t row, const std::size_t column) const;

  //! Return the inverse matrix
  Matrix inverseMatrix() const;

  //! Check if the matrix is square matrix
  static constexpr bool isSquareMatrix()
  {
    return kRow == kColumn;
  }

  //! Calculate the minor determinant
  Arithmetic minorDeterminant(const std::size_t row, const std::size_t column) const;

  //! Return row size
  static constexpr std::size_t rowSize()
  {
    return kRow;
  }

  //! Set element
  void set(const std::size_t row, const std::size_t column, const Arithmetic value);

  //! Return the transposed matrix
  Matrix<Arithmetic, kColumn, kRow> transposedMatrix() const;

 private:
  ArrayType elements_;
};

//! Multiply two matrixes
template <typename Arithmetic, std::size_t L, std::size_t M, std::size_t N>
Matrix<Arithmetic, L, N> operator*(const Matrix<Arithmetic, L, M>& a,
                                   const Matrix<Arithmetic, M, N>& b);

//! Multiply two matrixes
template <typename Arithmetic, std::size_t kRow, std::size_t kColumn>
Matrix<Arithmetic, kRow, kColumn> operator*(
    const Arithmetic scalar,
    const Matrix<Arithmetic, kRow, kColumn>& matrix);

//! Multiply a matrix and a array
template <typename Arithmetic, std::size_t kN>
ArithmeticArray<Arithmetic, kN> operator*(
    const Matrix<Arithmetic, kN, kN>& matrix,
    const ArithmeticArray<Arithmetic, kN>& array);

//! Multiply a matrix and a point
template <typename Arithmetic, std::size_t kN>
Point<Arithmetic, kN> operator*(const Matrix<Arithmetic, kN, kN>& matrix,
                                const Point<Arithmetic, kN>& point);

//! Multiply a matrix and a point
template <typename Arithmetic, std::size_t kN>
Vector<Arithmetic, kN> operator*(const Matrix<Arithmetic, kN, kN>& matrix,
                                 const Vector<Arithmetic, kN>& vector);

} // namespace zisc

#include "matrix-inl.hpp"

#endif // _ZISC_MATRIX_HPP_
