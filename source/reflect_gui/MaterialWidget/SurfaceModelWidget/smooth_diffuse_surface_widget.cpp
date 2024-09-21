/*!
  \file smooth_diffuse_surface_widget.cpp
  \author takemura
  */

#include "smooth_diffuse_surface_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_widget.hpp"
#include "MaterialWidget/texture_weight_widget.hpp"
// UI
#include "ui_smooth_diffuse_surface_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
SmoothDiffuseSurfaceWidget::SmoothDiffuseSurfaceWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SmoothDiffuseSurfaceWidget::readData(const QString& prefix, 
                                          const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::reflectance;
  reflectance_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void SmoothDiffuseSurfaceWidget::validateData(QStringList* error_message_list) const
{
  reflectance_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void SmoothDiffuseSurfaceWidget::writeData(const QString& prefix, 
                                           QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::reflectance;
  reflectance_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void SmoothDiffuseSurfaceWidget::initialize()
{
  ui_.setupUi(this);

  reflectance_widget_ = new TextureWeightWidget{ui_.reflectance_frame};
  reflectance_widget_->activate();
}

} // namespace reflect
