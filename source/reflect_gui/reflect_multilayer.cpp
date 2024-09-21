/*!
  \file reflect_multilayer.cpp
  \author takemura
  */

#include "reflect_multilayer.hpp"
// Qt
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectGui
#include "reflect_layer.hpp"
#include "widget_connection.hpp"
#include "Command/delete_object_command.hpp"
#include "Command/function_command.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ReflectMultilayer::ReflectMultilayer(QWidget* parent) :
    ReflectWidget(parent),
    layer_list_{nullptr}
{
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::activate()
{
  show();
  updateLayerNumber();
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::addLayer(ReflectLayer* layer)
{
  layer->setLayerList(layer_list_);
  layer_list_->insertItem(0, layer);
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::setDeleteLayerButton(QPushButton* button)
{
  auto delete_layer = [this]()
  {
    auto* layer = cast<ReflectListItem*>(layer_list_->currentItem());
    const auto text = QStringLiteral("Delete %1 layer.").arg(layer->text());
    const int row = layer_list_->currentRow();
    auto take_function = [this, row]()
    {
      auto* item = cast<ReflectListItem*>(layer_list_->takeItem(row));
      layer_list_->setCurrentItem(nullptr);
      updateLayerNumber();
      return item;
    };
    auto insert_function = [this, row](ReflectListItem* item)
    {
      layer_list_->insertItem(row, item);
      item->activate();
      layer_list_->setCurrentItem(nullptr);
      updateLayerNumber();
    };

    auto* command = new DeleteObjectCommand<ReflectListItem>{text, 
                                                             take_function, 
                                                             insert_function};
    auto* window = ReflectWidget::mainWindow();
    window->appendCommand(command);
  };
  connection_list_ << connectButton(button, delete_layer);
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::setLayerList(QListWidget* layer_list)
{
  layer_list_ = layer_list;
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::setMoveDownButton(QPushButton* button)
{
  auto move_down_layer = [this]()
  {
    auto* layer = cast<ReflectListItem*>(layer_list_->currentItem());
    const auto text = QStringLiteral("Move down %1 layer.").arg(layer->text());
    const int row = layer_list_->currentRow();
    auto function1 = [this, row]()
    {
      auto* item = layer_list_->takeItem(row);
      layer_list_->insertItem(row + 1, item);
      cast<ReflectListItem*>(item)->activate();
      layer_list_->setCurrentItem(item);
      updateLayerNumber();
    };
    auto function2 = [this, row]()
    {
      auto* item = layer_list_->takeItem(row + 1);
      layer_list_->insertItem(row, item);
      cast<ReflectListItem*>(item)->activate();
      layer_list_->setCurrentItem(item);
      updateLayerNumber();
    };
    
    auto* command = new FunctionCommand{text, function1, function2};

    auto* window = ReflectWidget::mainWindow();
    window->appendCommand(command);
  };
  connection_list_ << connectButton(button, move_down_layer);
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::setMoveUpButton(QPushButton* button)
{
  auto move_up_layer = [this]()
  {
    auto* layer = cast<ReflectListItem*>(layer_list_->currentItem());
    const auto text = QStringLiteral("Move up %1 layer.").arg(layer->text());
    const int row = layer_list_->currentRow();
    auto function1 = [this, row]()
    {
      auto* item = layer_list_->takeItem(row);
      layer_list_->insertItem(row - 1, item);
      cast<ReflectListItem*>(item)->activate();
      layer_list_->setCurrentItem(item);
      updateLayerNumber();
    };
    auto function2 = [this, row]()
    {
      auto* item = layer_list_->takeItem(row - 1);
      layer_list_->insertItem(row, item);
      cast<ReflectListItem*>(item)->activate();
      layer_list_->setCurrentItem(item);
      updateLayerNumber();
    };

    auto* command = new FunctionCommand{text, function1, function2};

    auto* window = ReflectWidget::mainWindow();
    window->appendCommand(command);
  };
  connection_list_ << connectButton(button, move_up_layer);
}

/*!
  \details
  No detailed.
  */
void ReflectMultilayer::updateLayerNumber()
{
  if (layer_list_ == nullptr)
    return;

  const int count = layer_list_->count();
  for (int i = 0; i < count; ++i) {
    auto* layer = cast<ReflectLayer*>(layer_list_->item(i));
    layer->setNumber(count - i);
  }
}

} // namespace reflect
