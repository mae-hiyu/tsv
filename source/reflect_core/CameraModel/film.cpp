/*!
 \file film.cpp
 \author takemura
 */

#include "film.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/utility.hpp"
// Reflect
#include "keyword.hpp"
#include "Color/rgb_spectra_image.hpp"
#include "Color/spectra_image.hpp"
#include "RendererBase/color_system.hpp"
#include "RendererBase/renderer_base.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
 \details
 No detailed.
 */
Film::Film(const ColorSystem& color_system,
           const QSettings& settings, 
           const QString& prefix)
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
void Film::initialize(const ColorSystem& color_system,
                      const QSettings& settings, 
                      const QString& prefix)
{
  jittering_ = value<bool>(settings, prefix + "/" + keyword::jittering);

  // Image resolution
  width_ = value<std::size_t>(settings, prefix + "/" + keyword::image_width);
  height_ = value<std::size_t>(settings, prefix + "/" + keyword::image_height);
  inverse_width_ = 1.0 / cast<double>(width_);
  inverse_height_ = 1.0 / cast<double>(height_);

  // Initialize buffer
  if (color_system.isRgbRenderingMode())
    spectra_buffer_ = new RgbSpectraImage{width_, height_};
  else
    spectra_buffer_ = new XYZSpectraImage{width_, height_};
}

/*!
  \details
  No detailed.
  */
std::size_t Film::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(width_);
  size += PRINT_VARIABLE_DATA(height_);
  size += PRINT_VARIABLE_DATA(inverse_width_);
  size += PRINT_VARIABLE_DATA(inverse_height_);
  size += PRINT_VARIABLE_DATA(spectra_buffer_);
  size += PRINT_VARIABLE_DATA(jittering_);
  return size;
}

} // namespace reflect
