/*!
  \file material_item.cpp
  \author takemura
  */

#include "material_item.hpp"
// Qt
#include <QString>

namespace reflect {

/*!
  \details
  No detailed.
  */
template <>
QString SurfaceModelItem::getTypeName()
{
  return QStringLiteral("Surface model");
}

/*!
  \details
  No detailed.
  */
template <>
QString EmitterModelItem::getTypeName()
{
  return QStringLiteral("Emitter model");
}

/*!
  \details
  No detailed.
  */
template <>
QString TextureItem::getTypeName()
{
  return QStringLiteral("Texture");
}

} // namespace reflect
