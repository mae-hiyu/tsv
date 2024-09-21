/*!
  \file multilayer_thin_film_widget.cpp
  \author takemura
  */

#include "multilayer_thin_film_widget.hpp"
// Qt
#include <QCheckBox>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_multilayer.hpp"
#include "reflect_widget.hpp"
#include "thin_film_item.hpp"
#include "widget_connection.hpp"
#include "MaterialWidget/spectrum_palette_widget.hpp"
// UI
#include "ui_multilayer_thin_film_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
MultilayerThinFilmWidget::MultilayerThinFilmWidget(QWidget* parent) :
    ReflectMultilayer(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmWidget::readData(const QString& prefix,
                                        const QSettings& settings)
{
  auto key = prefix + "/" + keyword::is_conductor;
  const auto is_conductor = settings.value(key, false);
  ui_.interior_conductor_checkbox->setChecked(is_conductor.toBool());

  key = prefix + "/" + keyword::exterior_refractive_index;
  exterior_refractive_index_widget_->readData(key, settings);

  key = prefix + "/" + keyword::interior_refractive_index;
  interior_refractive_index_widget_->readData(key, settings);

  if (is_conductor.toBool()) {
    key = prefix + "/" + keyword::interior_extinction;
    interior_extinction_widget_->readData(key, settings);
  }

  key = prefix + "/" + keyword::count;
  const int count = settings.value(key).toInt();
  for (int index = 0; index < count; ++index) {
    const auto layer_number = prefix + "/" + QString{keyword::item}.arg(index);
    auto* layer = new ThinFilmItem{};
    addLayer(layer);
    layer->activate();
    layer->readData(layer_number, settings);
  }

  activate();
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmWidget::validateData(QStringList* error_message_list)
    const
{
  exterior_refractive_index_widget_->validateData(error_message_list);
  interior_refractive_index_widget_->validateData(error_message_list);
  if (ui_.interior_conductor_checkbox->isChecked())
    interior_extinction_widget_->validateData(error_message_list);

  const int count = ui_.thin_film_layer_list->count();
  for (int index = 0; index < count; ++index) {
    auto* layer =
        cast<ReflectLayer*>(ui_.thin_film_layer_list->item(count -1 - index));
    layer->validateData(error_message_list);
  }
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmWidget::writeData(const QString& group,
                                         QSettings* settings) const
{
  const auto is_conductor = table_[keyword::is_conductor];
  settings->setValue(group + "/" + keyword::is_conductor, is_conductor);

  QString prefix{group + "/" + keyword::exterior_refractive_index};
  exterior_refractive_index_widget_->writeData(prefix, settings);

  prefix = group + "/" + keyword::interior_refractive_index;
  interior_refractive_index_widget_->writeData(prefix, settings);

  if (is_conductor.toBool()) {
    prefix = group + "/" + keyword::interior_extinction;
    interior_extinction_widget_->writeData(prefix, settings);
  }

  settings->beginGroup(group);

  const int count = ui_.thin_film_layer_list->count();
  settings->setValue(keyword::count, count);
  for (int index = 0; index < count; ++index) {
    const auto layer_number = QString{keyword::item}.arg(index);
    auto* layer =
        cast<ReflectLayer*>(ui_.thin_film_layer_list->item(count -1 - index));
    layer->writeData(layer_number, settings);
  }

  settings->endGroup();
}

/*!
  \details
  No detailed.
  */
void MultilayerThinFilmWidget::initialize()
{
  ui_.setupUi(this);

  setLayerList(ui_.thin_film_layer_list);
  setAddLayerButton<ThinFilmItem>(ui_.add_button);
  setDeleteLayerButton(ui_.delete_button);
  setMoveDownButton(ui_.down_button);
  setMoveUpButton(ui_.up_button);

  auto enable_conductor = [this](const bool enabled)
  {
    constexpr auto key = keyword::is_conductor;
    table_[key].setValue(enabled);
    ui_.interior_extinction_frame->setEnabled(enabled);
  };
  connection_list_ << connectCheckBox(ui_.interior_conductor_checkbox, enable_conductor);
  enable_conductor(ui_.interior_conductor_checkbox->isChecked());

  auto* exterior_refractive_index_widget =
      new SpectrumPaletteWidget{ui_.exterior_refractive_index_frame};
  exterior_refractive_index_widget->setText("Refractive index");
  exterior_refractive_index_widget_ = exterior_refractive_index_widget;

  auto* interior_refractive_index_widget =
      new SpectrumPaletteWidget{ui_.interior_refractive_index_frame};
  interior_refractive_index_widget->setText("Refractive index");
  interior_refractive_index_widget_ = interior_refractive_index_widget;

  auto* interior_extinction_widget =
      new SpectrumPaletteWidget{ui_.interior_extinction_frame};
  interior_extinction_widget->setText("Extinction");
  interior_extinction_widget_ = interior_extinction_widget;
}

} // namespace reflect
