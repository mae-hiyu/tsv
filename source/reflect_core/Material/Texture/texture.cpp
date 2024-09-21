/*!
  \file texture.cpp
  \author takemura
  */

#include "texture.hpp"
// Standard C++ library
#include <cstddef>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Reflect
#include "checkerboard_texture.hpp"
#include "keyword.hpp"
#include "image_texture.hpp"
#include "unicolor_texture.hpp"
#include "value_texture.hpp"
#include "Color/spectral_distribution.hpp"
#include "RendererBase/color_system.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SpectralDistribution Texture::weight() const
{
  zisc::raiseError("TextureError: (type=", cast<int>(type()),
                   ") weight method is not implemented.");
  return SpectralDistribution{};
}

/*!
  \details
  No detailed.
  */
UniquePointer<Texture> makeTexture(const ColorSystem& color_system,
                                   const QSettings& settings,
                                   const QString& prefix)
{
  Texture* texture = nullptr;

  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::value_texture):
    texture = new ValueTexture{color_system, settings, prefix};
    break;
   case zisc::toHash32(keyword::unicolor_texture):
    texture = new UnicolorTexture{color_system, settings, prefix};
    break;
   case zisc::toHash32(keyword::checkerboard_texture):
    texture = new CheckerboardTexture{color_system, settings, prefix};
    break;
   case zisc::toHash32(keyword::image_texture):
    texture = new ImageTexture{color_system, settings, prefix};
    break;
   default:
    zisc::raiseError("TextureError: Unsupported type is specified.");
    break;
  }

  return UniquePointer<Texture>{texture};
}

//! Get a texture
const Texture* getTexture(const QSettings& settings,
                          const QString& prefix,
                          const std::vector<const Texture*>& texture_list)
{
  const auto key = prefix + "/" + keyword::texture_index;
  const std::size_t index = value<std::size_t>(settings, key);
  return texture_list[index];
}

} // namespace reflect
