/*!
  \file transformation_widget.cpp
  \author takemura
  */

#include "transformation_widget.hpp"
// Standard C++ library
#include <functional>
// Qt
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "reflect_layer.hpp"
#include "reflect_main_window.hpp"
#include "reflect_multilayer.hpp"
#include "reflect_widget.hpp"
#include "rotation_item.hpp"
#include "scaling_item.hpp"
#include "translation_item.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
TransformationWidget::TransformationWidget(QWidget* parent) :
    ReflectMultilayer(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void TransformationWidget::readData(const QString& prefix, 
                                    const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::count;
  const int count = settings.value(key).toInt();
  for (int index = 0; index < count; ++index) {
    const auto layer_number = prefix + "/" + QString{keyword::item}.arg(index);
    auto* layer = makeTransformationItem(layer_number, settings);
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
void TransformationWidget::initialize()
{
  ui_.setupUi(this);

  setLayerList(ui_.transformation_list); 
  setAddLayerButton<TranslationItem>(ui_.translation_button);
  setAddLayerButton<ScalingItem>(ui_.scaling_button);
  setAddLayerButton<RotationItem>(ui_.rotation_button);
  setDeleteLayerButton(ui_.delete_button);
  setMoveDownButton(ui_.down_button);
  setMoveUpButton(ui_.up_button);

  auto enable_button = [this](QListWidgetItem* current, QListWidgetItem* /* previous */)
  {
    const bool enabled = current != nullptr;
    ui_.delete_button->setEnabled(enabled);
    const int row = ui_.transformation_list->currentRow();
    ui_.up_button->setEnabled(enabled && (row > 0));
    ui_.down_button->setEnabled(enabled && 
                                (row < ui_.transformation_list->count() - 1));
  };
  connection_list_ << connect(ui_.transformation_list, 
                              &QListWidget::currentItemChanged, 
                              enable_button);
}

/*!
  \details
  No detailed.
  */
void TransformationWidget::setScalingEnabled(const bool enabled)
{
  ui_.scaling_button->setEnabled(enabled);
}

/*!
  \details
  No detailed.
  */
void TransformationWidget::writeData(const QString& prefix, 
                                     QSettings* settings) const
{
  const int count = ui_.transformation_list->count();
  const auto key = prefix + "/" + keyword::count;
  settings->setValue(key, count);
  for (int index = 0; index < count; ++index) {
    const auto layer_number = prefix + "/" + QString{keyword::item}.arg(index);
    const int number = count - 1 - index;
    auto* layer = cast<ReflectLayer*>(ui_.transformation_list->item(number));
    layer->writeData(layer_number, settings);
  }
}

/*!
  \details
  No detailed.
  */
ReflectLayer* makeTransformationItem(const QString& prefix, 
                                     const QSettings& settings)
{
  ReflectLayer* layer = nullptr;

  const auto key = prefix + "/" + keyword::name;
  const auto name = settings.value(key).toString();
  switch (zisc::toHash32(name.toStdString().c_str())) {
   case zisc::toHash32(keyword::translation):
    layer = new TranslationItem{};
    break;
   case zisc::toHash32(keyword::scaling):
    layer = new ScalingItem{};
    break;
   case zisc::toHash32(keyword::rotation):
    layer = new RotationItem{};
    break;
   default:
    zisc::raiseError("TransformationError: Unsupported type is specified.");
    break;
  }

  return layer;

}

} // namespace reflect
