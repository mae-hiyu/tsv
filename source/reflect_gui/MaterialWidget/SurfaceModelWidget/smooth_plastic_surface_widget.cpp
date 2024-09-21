/*!
  \file smooth_plastic_surface_widget.cpp
  \author takemura
  */

#include "smooth_plastic_surface_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/set_value_command.hpp"
#include "MaterialWidget/spectrum_palette_widget.hpp"
#include "MaterialWidget/texture_weight_widget.hpp"
// UI
#include "ui_smooth_plastic_surface_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
SmoothPlasticSurfaceWidget::SmoothPlasticSurfaceWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SmoothPlasticSurfaceWidget::readData(const QString& prefix, 
                                            const QSettings& settings)
{
  auto key = prefix + "/" + keyword::exterior_refractive_index;
  exterior_refractive_index_widget_->readData(key, settings);

  key = prefix + "/" + keyword::interior_refractive_index;
  interior_refractive_index_widget_->readData(key, settings);

  key = prefix + "/" + keyword::reflectance;
  diffuse_reflectance_widget_->readData(key, settings);

  key = prefix + "/" + keyword::weight;
  const auto weight = settings.value(key, 400);
  ui_.specular_weight_spinbox->setValue(weight.toInt());
}

/*!
  \details
  No detailed.
  */
void SmoothPlasticSurfaceWidget::validateData(QStringList* error_message_list) 
    const
{
  exterior_refractive_index_widget_->validateData(error_message_list);
  interior_refractive_index_widget_->validateData(error_message_list);
  diffuse_reflectance_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void SmoothPlasticSurfaceWidget::writeData(const QString& prefix,
                                           QSettings* settings) const
{
  auto key = prefix + "/" + keyword::exterior_refractive_index;
  exterior_refractive_index_widget_->writeData(key, settings);

  key = prefix + "/" + keyword::interior_refractive_index;
  interior_refractive_index_widget_->writeData(key, settings);

  key = prefix + "/" + keyword::reflectance;
  diffuse_reflectance_widget_->writeData(key, settings);

  key = prefix + "/" + keyword::weight;
  settings->setValue(key, table_[keyword::weight]);
}

/*!
  \details
  No detailed.
  */
void SmoothPlasticSurfaceWidget::initialize()
{
  ui_.setupUi(this);

  exterior_refractive_index_widget_ = 
      new SpectrumPaletteWidget{ui_.exterior_refractive_index_frame};
  exterior_refractive_index_widget_->activate();

  interior_refractive_index_widget_ =
      new SpectrumPaletteWidget{ui_.interior_refractive_index_frame};
  interior_refractive_index_widget_->activate();

  diffuse_reflectance_widget_ = 
      new TextureWeightWidget{ui_.diffuse_reflectance_frame};
  diffuse_reflectance_widget_->activate();

  auto update_specular_weight = [this](const int n)
  {
    ui_.specular_weight_spinbox->setValue(n);
  };

  auto set_specular_weight = [this, update_specular_weight](const int n)
  {
    constexpr auto key = keyword::weight;
    auto* window = ReflectWidget::mainWindow();
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set specular weight to %1.").arg(n);
      const int old_n = table_[key].toInt();
      auto* command = new SetValueCommand<int>{text, n, old_n, update_specular_weight};
      window->appendCommand(command);
    }
    table_[key].setValue(n);
  };
  connection_list_ << connectSpinBox(ui_.specular_weight_spinbox, set_specular_weight);
}

} // namespace reflect
