/*!
  \file thin_film_item.cpp
  \author takemura
  */

#include "thin_film_item.hpp"
// Standard C++ library
#include <functional>
// Qt
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_layer.hpp"
#include "reflect_object.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "MaterialWidget/spectrum_palette_widget.hpp"
// UI
#include "ui_thin_film_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ThinFilmItem::ThinFilmItem()
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ThinFilmItem::validateData(QStringList* error_message_list) const
{
  refractive_index_widget_->validateData(error_message_list);
  if (ui_.conductor_checkbox->isChecked())
    extinction_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void ThinFilmItem::initialize()
{
  setName("ThinFilm");

  table_[keyword::is_conductor].setValue(true);
  table_[keyword::thickness].setValue(10.0);
}

/*!
  \details
  No detailed.
  */
void ThinFilmItem::writeData(const QString& prefix, QSettings* settings) const
{
  writeTableData(prefix, settings);
  auto key = prefix + "/" + keyword::refractive_index;
  refractive_index_widget_->writeData(key, settings);
  const bool is_conductor = table_[keyword::is_conductor].toBool();
  if (is_conductor) {
    key = prefix + "/" + keyword::extinction_coefficient;
    extinction_widget_->writeData(key, settings);
  }
}

/*!
  \details
  No detailed.
  */
void ThinFilmItem::initializeLayerFrame(QWidget* frame)
{
  resetConnection();
  if (!item_widget_.isNull())
    delete item_widget_;

  item_widget_ = new QWidget{frame};
  ui_.setupUi(item_widget_);

  auto enable_conductor = [this](const bool enabled)
  {
    constexpr auto key = keyword::is_conductor;
    table_[key].setValue(enabled);
    ui_.extinction_frame->setEnabled(enabled);
  };
  connection_list_ << connectCheckBox(ui_.conductor_checkbox, enable_conductor);
  enable_conductor(table_[keyword::is_conductor].toBool());

  auto set_thickness = [this](const double thickness)
  {
    constexpr auto key = keyword::thickness;
    table_[key].setValue(thickness);
  };
  connection_list_ << connectSpinBox(ui_.thickness_spinbox, set_thickness);
  set_thickness(table_[keyword::thickness].toDouble());

  auto* refractive_index_widget =
      new SpectrumPaletteWidget{ui_.refractive_index_frame};
  refractive_index_widget->setText("Refractive index");
  refractive_index_widget_ = refractive_index_widget;

  auto* extinction_widget = new SpectrumPaletteWidget{ui_.extinction_frame};
  extinction_widget->setText("Extinction");
  extinction_widget_ = extinction_widget;
}

/*!
  \details
  No detailed.
  */
void ThinFilmItem::readLayerData(const QString& prefix,
                                 const QSettings& settings)
{
  auto key = prefix + "/" + keyword::is_conductor;
  const auto is_conductor = settings.value(key, false);
  ui_.conductor_checkbox->setChecked(is_conductor.toBool());

  key = prefix + "/" + keyword::thickness;
  const auto thickness = settings.value(key, 10.0);
  ui_.thickness_spinbox->setValue(thickness.toDouble());

  key = prefix + "/" + keyword::refractive_index;
  refractive_index_widget_->readData(key, settings);

  if (is_conductor.toBool()) {
    key = prefix + "/" + keyword::extinction_coefficient;
    extinction_widget_->readData(key, settings);
  }
}

} // namespace reflect
