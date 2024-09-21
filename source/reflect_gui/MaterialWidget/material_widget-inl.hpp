/*!
  \file material_widget-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_WIDGET_INL_HPP_
#define _REFLECT_MATERIAL_WIDGET_INL_HPP_

#include "material_widget.hpp"
// Standard C++ library
#include <memory>
#include <utility>
// Qt
#include <QListWidget>
#include <QListWidgetItem>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "material_item.hpp"
#include "material_item_type.hpp"
#include "material_list_manager.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "reflect_widget_item.hpp"
#include "widget_connection.hpp"
#include "Command/add_object_command.hpp"
#include "Command/delete_object_command.hpp"
// UI
#include "ui_material_widget.h"

namespace reflect {

using zisc::cast;

template <MaterialItemType kType> inline
MaterialWidget<kType>::MaterialWidget(QWidget* parent) :
    ReflectWidget{parent}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
QWidget* MaterialWidget<kType>::itemFrame() const
{
  return ui_.material_item_frame;
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
const MaterialListManager* MaterialWidget<kType>::manager() const
{
  return &manager_;
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
QListWidget* MaterialWidget<kType>::materialListWidget() const
{
  return ui_.material_list;
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
void MaterialWidget<kType>::readData(const QString& prefix, const QSettings& settings)
{
  // Clear buffer
  ui_.material_list->clear();

  using Material = MaterialItem<kType>;
  const auto key = prefix + "/" + keyword::count;
  const int count = settings.value(key).toInt();
  for (int index = 0; index < count; ++index) {
    const auto item_id = prefix + "/" + QString{keyword::item}.arg(index);
    auto* item = new Material{this};
    item->readData(item_id, settings);
    ui_.material_list->addItem(item);
    item->deactivate();
  }

  ui_.material_list->setCurrentItem(nullptr);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
void MaterialWidget<kType>::validateData(QStringList* error_message_lsit) const
{
  const int count = ui_.material_list->count();
  for (int index = 0; index < count; ++index) {
    auto* item = cast<ReflectListItem*>(ui_.material_list->item(index));
    item->validateData(error_message_lsit);
  }
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
void MaterialWidget<kType>::writeData(const QString& prefix, 
                                      QSettings* settings) const
{
  const int count = ui_.material_list->count();
  const auto key = prefix + "/" + keyword::count;
  settings->setValue(key, count);
  for (int index = 0; index < count; ++index) {
    const auto item_id = prefix + "/" + QString{keyword::item}.arg(index);
    auto* item = cast<ReflectListItem*>(ui_.material_list->item(index));
    item->writeData(item_id, settings);
  }
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
void MaterialWidget<kType>::initialize()
{
  ui_.setupUi(this);

  using Material = MaterialItem<kType>;

  auto select_item = [this](QListWidgetItem* current, QListWidgetItem* previous)
  {
    auto* previous_item = cast<ReflectListItem*>(previous);
    if (previous_item != nullptr)
      previous_item->deactivate();
    auto* current_item = cast<ReflectListItem*>(current);
    if (current_item != nullptr)
      current_item->activate();
  };
  connection_list_ <<
      connect(ui_.material_list, &QListWidget::currentItemChanged, select_item);

  auto enable_button = [this](QListWidgetItem* current, 
                              QListWidgetItem* /* previous */)
  {
    const bool enabled = current != nullptr;
    ui_.delete_material_button->setEnabled(enabled);
  };
  connection_list_ <<
      connect(ui_.material_list, &QListWidget::currentItemChanged, enable_button);

  auto edit_name = [this](QListWidgetItem* item)
  {
    auto* material_item = cast<Material*>(item);
    const auto old_name = material_item->name();
    const auto new_name = material_item->text();
    if (new_name == old_name)
      return;
    material_item->setName(new_name);

    const int index = ui_.material_list->row(item);
    emit manager_.listItemEdited(index, new_name);
  };
  connection_list_ << connect(ui_.material_list, &QListWidget::itemChanged, edit_name);

  auto add_item = [this]()
  {
    auto* window = ReflectWidget::mainWindow();
    window->disableCommandLogging();

    const auto message = QStringLiteral("Add a \"%1\" material.");
    const auto text = message.arg(Material::getTypeName());
    auto material = std::unique_ptr<Material>{new Material{this}};

    auto add = [this](Material* material)
    {
      ui_.material_list->addItem(material);
      const int row = ui_.material_list->count();
      emit manager_.listItemInserted(row, material->text());
      ui_.material_list->setCurrentItem(nullptr);
    };

    auto take = [this]()
    {
      const int row = ui_.material_list->count() - 1;
      auto* material = cast<Material*>(ui_.material_list->takeItem(row));
      emit manager_.listItemDeleted(row);
      ui_.material_list->setCurrentItem(nullptr);
      return material;
    };

    auto* command = 
        new AddObjectCommand<Material>{text, std::move(material), add, take};
    window->appendCommand(command);

    window->enableCommandLogging();
  };
  connection_list_ << connectButton(ui_.add_material_button, add_item);

  auto delete_item = [this]()
  {
    auto* item = cast<Material*>(ui_.material_list->currentItem());
    const auto message = QStringLiteral("Delete %1 material.");
    const auto text = message.arg(item->name());
    const int row = ui_.material_list->currentRow();
    auto take = [this, row]()
    {
      auto* material = cast<Material*>(ui_.material_list->takeItem(row));
      ui_.material_list->setCurrentItem(nullptr);
      emit manager_.listItemDeleted(row);
      return material;
    };
    auto insert = [this, row](Material* material)
    {
      ui_.material_list->insertItem(row, material);
      ui_.material_list->setCurrentItem(nullptr);
      emit manager_.listItemInserted(row, material->text());
    };

    auto* command = new DeleteObjectCommand<Material>{text, take, insert};
    auto* window = ReflectWidget::mainWindow();
    window->appendCommand(command);
  };
  connection_list_ << connectButton(ui_.delete_material_button, delete_item);
}

} // namespace reflect

#endif // _REFLECT_MATERIAL_WIDGET_INL_HPP_
