/*!
  \file reflect_layer.cpp
  \author takemura
  */

#include "reflect_layer.hpp"
// Qt
#include <QCheckBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_widget_item.hpp"
#include "widget_connection.hpp"
// UI
#include "ui_layer_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ReflectLayer::ReflectLayer()
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ReflectLayer::activate()
{
  initializeWidget();
  setSizeHint(layer_widget_->size());
  layer_list_->setItemWidget(this, layer_widget_);
}

/*!
  \details
  No detailed.
  */
void ReflectLayer::readData(const QString& prefix, const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::enabled;
  const auto enabled = settings.value(key, false);
  ui_.enable_checkbox->setChecked(enabled.toBool());

  readLayerData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ReflectLayer::setLayerList(QListWidget* layer_list)
{
  layer_list_ = layer_list;
}

/*!
  \details
  No detailed.
  */
void ReflectLayer::setNumber(const int number)
{
  ui_.enable_checkbox->setText(QString::number(number));
}

/*!
  \details
  No detailed.
  */
void ReflectLayer::initialize()
{
  table_[keyword::enabled].setValue(true);
}

/*!
  \details
  No detailed.
  */
void ReflectLayer::initializeWidget()
{
  resetConnection();
  if (!layer_widget_.isNull())
    delete layer_widget_;

  layer_widget_ = new QWidget{nullptr};
  ui_.setupUi(layer_widget_);
  ui_.name_label->setText(name());

  initializeLayerFrame(ui_.layer_frame);

  auto enable_layer = [this](const bool enabled)
  {
    ui_.name_label->setEnabled(enabled);
    ui_.layer_frame->setEnabled(enabled);
    table_[keyword::enabled].setValue(enabled);
  };
  const bool enabled = table_[keyword::enabled].toBool();
  ui_.enable_checkbox->setChecked(enabled);
  connection_list_ << connectCheckBox(ui_.enable_checkbox, enable_layer);
  enable_layer(enabled);
}

} // namespace reflect
