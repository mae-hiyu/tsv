/*!
  \file transformation.hpp
  \author takemura
  */

#ifndef _REFLECT_TRANSFORMATION_HPP_
#define _REFLECT_TRANSFORMATION_HPP_

// Standard C++ library
#include <vector>
// Zisc
#include "reflect_config.hpp"
#include "zisc/matrix.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

//! \addtogroup LinearAlgebra
//! \{

using Matrix3x3 = zisc::Matrix<double, 3, 3>;
using Matrix4x4 = zisc::Matrix<double, 4, 4>;

//! Make transformation matrix
Matrix4x4 makeTransformationMatrix(const QSettings& settings, const QString& prefix);

//! Make translation matrix
Matrix4x4 makeTranslationMatrix(const QSettings& settings, const QString& prefix);

//! Make scaling matrix
Matrix4x4 makeScalingMatrix(const QSettings& settings, const QString& prefix);

//! Make rotation matrix
Matrix4x4 makeRotationMatrix(const QSettings& settings, const QString& prefix);

//! Make x axis rotation matrix
Matrix4x4 makeXAxisRotationMatrix(const double theta);

//! Make y axis rotation matrix
Matrix4x4 makeYAxisRotationMatrix(const double theta);

//! Make z axis rotation matrix
Matrix4x4 makeZAxisRotationMatrix(const double theta);

//! Apply affine transformation to a point
void affineTransform(const Matrix4x4& matrix, Point3* point);

//! Apply affine transformation to a vector
void affineTransform(const Matrix4x4& matrix, Vector3* vector);

//! \} LinearAlgebra

} // namespace reflect

#endif // _REFLECT_TRANSFORMATION_HPP_
