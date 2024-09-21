/*!
  \file color_system.cpp
  \author takemura
  */

#include "color_system.hpp"
// Standard C++ library
#include <cstddef>
#include <cstdint>
#include <vector>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "Color/rgb_color_matching_function.hpp"
#include "Color/xyz_color_matching_function.hpp"
#include "Tonemapping/tonemapping_method.hpp"
#include "Utility/size.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ColorSystem::ColorSystem(const QSettings& settings)
{
  initialize(settings);
}

/*!
  \details
  No detailed.
  */
void ColorSystem::initialize(const QSettings& settings)
{
  // Check rgb rendering mode
  auto key = QString{keyword::color_group} + "/" + keyword::rgb_rendering;
  is_rgb_rendering_mode_ = value<bool>(settings, key);

  // Color space
  key = QString{keyword::color_group} + "/" + keyword::color_space;
  color_space_ = zisc::toHash32(value<QString>(settings, key).toStdString().c_str());

  // Color matching function
  key = QString{keyword::color_group} + "/" + keyword::standard_observer;
  const auto standard_observer = value<QString>(settings, key);
  key = QString{keyword::color_group} + "/" + keyword::standard_illuminant;
  const auto standard_illuminant = value<QString>(settings, key);
  rgb_color_matching_function_ = new RgbColorMatchingFunction{};
  xyz_color_matching_function_ = new XyzColorMatchingFunction{standard_observer,
                                                              standard_illuminant};

  tonemapping_method_ = makeTonemappingMethod(settings, keyword::color_group);
}

/*!
  \details
  No detailed.
  */
std::size_t ColorSystem::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(is_rgb_rendering_mode_);
  size += PRINT_VARIABLE_DATA(color_space_);
  size += PRINT_VARIABLE_DATA(rgb_color_matching_function_);
  size += PRINT_VARIABLE_DATA(xyz_color_matching_function_);
  size += PRINT_VARIABLE_DATA(tonemapping_method_);
  return size;
}

} // namespace reflect
