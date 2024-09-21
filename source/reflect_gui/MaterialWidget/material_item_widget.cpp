/*!
  \file material_item_widget.cpp
  \author takemura
  */

#include "material_item_widget.hpp"
// Qt
#include <QString>
#include <QStringList>
// Zisc
#include "zisc/algorithm.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "material_item.hpp"
#include "reflect_widget.hpp"
#include "MaterialWidget/EmitterModelWidget/non_directional_emitter_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/multilayer_thin_film_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/rough_conductor_surface_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/rough_dielectric_surface_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/smooth_conductor_surface_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/smooth_diffuse_surface_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/smooth_dielectric_surface_widget.hpp"
#include "MaterialWidget/SurfaceModelWidget/smooth_plastic_surface_widget.hpp"
#include "MaterialWidget/TextureWidget/checkerboard_texture_widget.hpp"
#include "MaterialWidget/TextureWidget/image_texture_widget.hpp"
#include "MaterialWidget/TextureWidget/unicolor_texture_widget.hpp"
#include "MaterialWidget/TextureWidget/value_texture_widget.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
template <>
QStringList getMaterialTypeList<MaterialItemType::SurfaceModel>()
{
  QStringList list;
  list << QString{keyword::smooth_diffuse_surface};
  list << QString{keyword::smooth_dielectric_surface};
  list << QString{keyword::smooth_conductor_surface};
  list << QString{keyword::multilayer_thin_film_surface};
  list << QString{keyword::rough_dielectric_surface};
  list << QString{keyword::rough_conductor_surface};
  list << QString{keyword::smooth_plastic_surface};
  return list;
}

/*!
  \details
  No detailed.
  */
template <>
QStringList getMaterialTypeList<MaterialItemType::EmitterModel>()
{
  QStringList list;
  list << QString{keyword::non_directional_emitter};
  return list;
}

/*!
  \details
  No detailed.
  */
template <>
QStringList getMaterialTypeList<MaterialItemType::Texture>()
{
  QStringList list;
  list << QString{keyword::value_texture};
  list << QString{keyword::unicolor_texture};
  list << QString{keyword::checkerboard_texture};
  list << QString{keyword::image_texture};
  return list;
}

/*!
  \details
  No detailed.
  */
template <>
ReflectWidget* makeMaterialItemWidget<MaterialItemType::SurfaceModel>(
    QWidget* parent, 
    const QString& type)
{
  ReflectWidget* widget = nullptr;
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::smooth_diffuse_surface):
    widget = new SmoothDiffuseSurfaceWidget{parent};
    break;
   case zisc::toHash32(keyword::smooth_dielectric_surface):
    widget = new SmoothDielectricSurfaceWidget{parent};
    break;
   case zisc::toHash32(keyword::smooth_conductor_surface):
    widget = new SmoothConductorSurfaceWidget{parent};
    break;
   case zisc::toHash32(keyword::multilayer_thin_film_surface):
    widget = new MultilayerThinFilmWidget{parent};
    break;
   case zisc::toHash32(keyword::rough_dielectric_surface):
    widget = new RoughDielectricSurfaceWidget{parent};
    break;
   case zisc::toHash32(keyword::rough_conductor_surface):
    widget = new RoughConductorSurfaceWidget{parent};
    break;
   case zisc::toHash32(keyword::smooth_plastic_surface):
    widget = new SmoothPlasticSurfaceWidget{parent};
    break;
   default:
    zisc::raiseError("SurfaceModelWidgetError: Unsupported type is specified.");
    break;
  }
  return widget;
}

/*!
  \details
  No detailed.
  */
template <>
ReflectWidget* makeMaterialItemWidget<MaterialItemType::EmitterModel>(
    QWidget* parent, 
    const QString& type)
{
  ReflectWidget* widget = nullptr;
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::non_directional_emitter):
    widget = new NonDirectionalEmitterWidget{parent};
    break;
   default:
    zisc::raiseError("EmitterModelWidgetError: Unsupported type is specified.");
    break;
  }
  return widget;
}

/*!
  \details
  No detailed.
  */
template <>
ReflectWidget* makeMaterialItemWidget<MaterialItemType::Texture>(
    QWidget* parent,
    const QString& type)
{
  ReflectWidget* widget = nullptr;
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::value_texture):
    widget = new ValueTextureWidget{parent};
    break;
   case zisc::toHash32(keyword::unicolor_texture):
    widget = new UnicolorTextureWidget{parent};
    break;
   case zisc::toHash32(keyword::checkerboard_texture):
    widget = new CheckerboardTextureWidget{parent};
    break;
   case zisc::toHash32(keyword::image_texture):
    widget = new ImageTextureWidget{parent};
    break;
   default:
    zisc::raiseError("TextureWidgetError: Unsupported type is specified.");
    break;
  }
  return widget;
}

} // namespace reflect
