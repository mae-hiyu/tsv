/*!
  \file tonemapping_method.cpp
  \author takemura
  */

#include "tonemapping_method.hpp"
// Standard C++ library
#include <cstddef>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/matrix.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "simplified_reinhard.hpp"
#include "reinhard.hpp"
#include "Color/color_space.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
TonemappingMethod::TonemappingMethod(const QSettings& settings,
                                     const QString& prefix)
{
  initialize(settings, prefix);
}

/*!
  \details
  No detailed.
  */
TonemappingMethod::~TonemappingMethod()
{
}

/*!
  \details
  No detailed.
  */
std::size_t TonemappingMethod::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(inverse_gamma_);
  size += PRINT_VARIABLE_DATA(to_rgb_matrix_);
  size += PRINT_VARIABLE_DATA(to_xyz_matrix_);
  return size;
}

/*!
  \details
  No detailed.
  */
void TonemappingMethod::initialize(const QSettings& settings, 
                                   const QString& prefix)
{
  QString key{prefix + "/" + keyword::gamma};
  inverse_gamma_ = 1.0 / value<double>(settings, key);

  key = prefix + "/" + keyword::color_space;
  const auto color_space = 
      zisc::toHash32(value<QString>(settings, key).toStdString().c_str());
  to_rgb_matrix_ = getXyzToRgbMatrix(color_space);
  to_xyz_matrix_ = getRgbToXyzMatrix(color_space);
}

/*!
  \details
  No detailed.
  */
UniquePointer<TonemappingMethod> makeTonemappingMethod(const QSettings& settings,
                                                       const QString& prefix)
{
  TonemappingMethod* method = nullptr;

  const auto type = value<QString>(settings, prefix + "/" + keyword::tonemapping);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::simplified_reinhard):
    method = new SimplifiedReinhard{settings, prefix};
    break;
   default:
    zisc::raiseError("TonemappingError: Unsupprted type is specified.");
    break;
  }

  return UniquePointer<TonemappingMethod>{method};
}

} // namespace reflect
