/*!
  \file smooth_dielectric_surface_widget.cpp
  \author takemura
  */

#include "smooth_dielectric_surface_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_widget.hpp"
#include "MaterialWidget/spectrum_palette_widget.hpp"
// UI
#include "ui_smooth_dielectric_surface_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
SmoothDielectricSurfaceWidget::SmoothDielectricSurfaceWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SmoothDielectricSurfaceWidget::readData(const QString& prefix, 
                                             const QSettings& settings)
{
  auto key = prefix + "/" + keyword::exterior_refractive_index;
  exterior_refractive_index_widget_->readData(key, settings);

  key = prefix + "/" + keyword::interior_refractive_index;
  interior_refractive_index_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void SmoothDielectricSurfaceWidget::validateData(QStringList* error_message_list) 
    const
{
  exterior_refractive_index_widget_->validateData(error_message_list);
  interior_refractive_index_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void SmoothDielectricSurfaceWidget::writeData(const QString& prefix,
                                              QSettings* settings) const
{
  auto key = prefix + "/" + keyword::exterior_refractive_index;
  exterior_refractive_index_widget_->writeData(key, settings);

  key = prefix + "/" + keyword::interior_refractive_index;
  interior_refractive_index_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void SmoothDielectricSurfaceWidget::initialize()
{
  ui_.setupUi(this);

  exterior_refractive_index_widget_ = 
      new SpectrumPaletteWidget{ui_.exterior_refractive_index_frame};
  exterior_refractive_index_widget_->activate();

  interior_refractive_index_widget_ =
      new SpectrumPaletteWidget{ui_.interior_refractive_index_frame};
  interior_refractive_index_widget_->activate();
}

} // namespace reflect
