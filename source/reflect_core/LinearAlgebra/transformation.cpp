/*!
  \file transformation.cpp
  \author takemura
  */

#include "transformation.hpp"
// Standard C++ library
#include <cmath>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/matrix.hpp"
#include "zisc/unit.hpp"
// Reflect
#include "keyword.hpp"
#include "point.hpp"
#include "reflect_config.hpp"
#include "Utility/value.hpp"

namespace reflect {

Matrix4x4 makeTransformationMatrix(const QSettings& settings, const QString& prefix)
{
  Matrix4x4 matrix{1.0, 0.0, 0.0, 0.0,
                   0.0, 1.0, 0.0, 0.0,
                   0.0, 0.0, 1.0, 0.0,
                   0.0, 0.0, 0.0, 1.0};

  const QString group = prefix + "/" + keyword::transformation;
  const int count = value<int>(settings, group + "/" + keyword::count);
  for (int index = 0; index < count; ++index) {
    const auto item_id = (group + "/" + keyword::item).arg(count - (index + 1));
    if (!value<bool>(settings, item_id + "/" + keyword::enabled))
      continue;
    const auto type = value<QString>(settings, item_id + "/" + keyword::name);
    switch (zisc::toHash32(type.toStdString().c_str())) {
     case zisc::toHash32(keyword::translation):
      matrix = matrix * makeTranslationMatrix(settings, item_id);
      break;
     case zisc::toHash32(keyword::scaling):
      matrix = matrix * makeScalingMatrix(settings, item_id);
      break;
     case zisc::toHash32(keyword::rotation):
      matrix = matrix * makeRotationMatrix(settings, item_id);
      break;
     default:
      zisc::raiseError("TransformationError: Unsupported type is specified.");
      break;
    }
  }
  return matrix;
}

/*!
  \details
  No detailed.
  */
Matrix4x4 makeTranslationMatrix(const QSettings& settings, const QString& prefix)
{
  const double x = value<double>(settings, prefix + "/" + keyword::x);
  const double y = value<double>(settings, prefix + "/" + keyword::y);
  const double z = value<double>(settings, prefix + "/" + keyword::z);
  return Matrix4x4{1.0, 0.0, 0.0,   x,
                   0.0, 1.0, 0.0,   y,
                   0.0, 0.0, 1.0,   z,
                   0.0, 0.0, 0.0, 1.0};
}

/*!
  \details
  No detailed.
  */
Matrix4x4 makeScalingMatrix(const QSettings& settings, const QString& prefix)
{
  const double x = value<double>(settings, prefix + "/" + keyword::x);
  const double y = value<double>(settings, prefix + "/" + keyword::y);
  const double z = value<double>(settings, prefix + "/" + keyword::z);
  return Matrix4x4{  x, 0.0, 0.0, 0.0,
                   0.0,   y, 0.0, 0.0,
                   0.0, 0.0,   z, 0.0,
                   0.0, 0.0, 0.0, 1.0};
}

/*!
  \details
  No detailed.
  */
Matrix4x4 makeRotationMatrix(const QSettings& settings, const QString& prefix)
{
  const auto angle_unit = 
      value<QString>(settings, prefix + "/" + keyword::angle_unit);
  const double angle = value<double>(settings, prefix + "/" + keyword::angle);
  const double theta = (angle_unit == keyword::degree_unit)
      ? zisc::toRadian(angle)
      : angle;

  Matrix4x4 matrix;
  const auto axis = value<QString>(settings, prefix + "/" + keyword::axis);
  switch (zisc::toHash32(axis.toStdString().c_str())) {
   case zisc::toHash32(keyword::x_axis):
    matrix = makeXAxisRotationMatrix(theta);
    break;
   case zisc::toHash32(keyword::y_axis):
    matrix = makeYAxisRotationMatrix(theta);
    break;
   case zisc::toHash32(keyword::z_axis):
    matrix = makeZAxisRotationMatrix(theta);
    break;
   default:
    zisc::raiseError("TransformationError: Unsupported axis is specified.");
    break;
  }
  return matrix;
}

/*!
  \details
  No detailed.
  */
Matrix4x4 makeXAxisRotationMatrix(const double theta)
{
  return Matrix4x4{1.0, 0.0            ,  0.0            , 0.0,
                   0.0, std::cos(theta), -std::sin(theta), 0.0,
                   0.0, std::sin(theta),  std::cos(theta), 0.0,
                   0.0, 0.0            ,  0.0            , 1.0}; 
}

/*!
  \details
  No detailed.
  */
Matrix4x4 makeYAxisRotationMatrix(const double theta)
{
  return Matrix4x4{ std::cos(theta), 0.0, std::sin(theta), 0.0,
                    0.0            , 1.0, 0.0            , 0.0,
                   -std::sin(theta), 0.0, std::cos(theta), 0.0,
                    0.0            , 0.0, 0.0            , 1.0};
}

/*!
  \details
  No detailed.
  */
Matrix4x4 makeZAxisRotationMatrix(const double theta)
{
  return Matrix4x4{std::cos(theta), -std::sin(theta), 0.0, 0.0,
                   std::sin(theta),  std::cos(theta), 0.0, 0.0,
                   0.0            ,  0.0            , 1.0, 0.0,
                   0.0            ,  0.0            , 0.0, 1.0};
}

/*!
  \details
  No detailed.
  */
void affineTransform(const Matrix4x4& matrix, Point3* point)
{
  *point = takePoint3(matrix * makePoint4(*point, 1.0));
}

/*!
  \details
  Please see the details of this algoriths below URL.
  http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/
  */
void affineTransform(const Matrix4x4& matrix, Vector3* vector)
{
  const Matrix3x3 normal_matrix{matrix(0, 0), matrix(0, 1), matrix(0, 2),
                                matrix(1, 0), matrix(1, 1), matrix(1, 2),
                                matrix(2, 0), matrix(2, 1), matrix(2, 2)};
  *vector = normal_matrix * *vector;
}


} // namespace reflect
