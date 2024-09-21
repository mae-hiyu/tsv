/*!
  \file ui_.object_tree.cpp
  \author takemura
  */

#include "object_tree.hpp"
// Standard C++ library
#include <memory>
#include <stack>
#include <utility>
// Qt
#include <QList>
#include <QPointer>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "object_tree_item.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "reflect_widget_item.hpp"
#include "widget_connection.hpp"
#include "Command/add_object_command.hpp"
#include "Command/delete_object_command.hpp"
#include "Command/function_command.hpp"
// UI
#include "ui_object_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ObjectTree::ObjectTree(QWidget* parent) :
    ReflectWidget(parent),
    is_object_move_mode_{false},
    selected_object_{nullptr}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
ObjectTree::~ObjectTree()
{
}

/*!
  \details
  No detailed.
  */
bool ObjectTree::isObjectMoveMode() const
{
  return is_object_move_mode_;
}

/*!
  \details
  No detailed.
  */
void ObjectTree::readData(const QString& prefix, const QSettings& settings)
{
  // Clear buffer
  ui_.object_tree->clear();

  const auto key = prefix + "/" + keyword::count;
  const int count = settings.value(key).toInt();
  for (int index = 0; index < count; ++index) {
    const auto item_id = prefix + "/" + QString{keyword::item}.arg(index);
    const auto type = settings.value(item_id + "/" + keyword::type).toString();
    auto* object_item = new ObjectTreeItem{type.toStdString().c_str()};
    object_item->readData(item_id, settings);
    ui_.object_tree->addTopLevelItem(object_item);
    object_item->deactivate();
  }

  ui_.object_tree->setCurrentItem(nullptr);
}

/*!
  \details
  No detailed.
  */
void ObjectTree::validateData(QStringList* error_message_list) const
{
  error_message_list->push_front(keyword::non_renderable); // For light source
  error_message_list->push_front(keyword::non_renderable); // For object

  QTreeWidgetItemIterator iterator{ui_.object_tree};
  while (*iterator) {
    const auto* item = cast<ReflectTreeItem*>(*iterator);
    item->validateData(error_message_list);
    ++iterator;
  }

  if (error_message_list->takeFirst() == keyword::non_renderable)
    (*error_message_list) << "The scene has no renderable object.";
  if (error_message_list->takeFirst() == keyword::non_renderable)
    (*error_message_list) << "The scene has no light source.";
}

/*!
  \details
  No detailed.
  */
void ObjectTree::writeData(const QString& prefix, QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::count;
  settings->setValue(key, ui_.object_tree->topLevelItemCount());

  auto* parent = ui_.object_tree->invisibleRootItem();
  for (int index = 0; index < parent->childCount(); ++index) {
    const auto item_id = prefix + "/" + QString{keyword::item}.arg(index);
    auto* object_item = cast<ObjectTreeItem*>(parent->child(index));
    object_item->writeData(item_id, settings);
  }
}

/*!
  \details
  No detailed.
  */
void ObjectTree::initialize()
{
  ui_.setupUi(this);

  auto show_setting_tab = [this](QTreeWidgetItem* current, QTreeWidgetItem* previous)
  {
    if (isObjectMoveMode())
      return;

    auto* previous_object_item = cast<ObjectTreeItem*>(previous);
    if (previous_object_item != nullptr)
      previous_object_item->deactivate();
    auto* current_object_item = cast<ObjectTreeItem*>(current);
    if (current_object_item != nullptr)
      current_object_item->activate();
  };
  connection_list_ <<
      connect(ui_.object_tree, &QTreeWidget::currentItemChanged, show_setting_tab);

  auto enable_button = [this](QTreeWidgetItem* current, 
                              QTreeWidgetItem* /* previous */)
  {
    auto* object_item = cast<ObjectTreeItem*>(current);

    if (isObjectMoveMode()) {
      ui_.move_button->setEnabled(object_item != nullptr && 
                                  object_item->type() == keyword::group_object);
      return;
    }

    if (object_item == nullptr) {
      ui_.delete_button->setEnabled(false);
      ui_.move_button->setEnabled(false);
    }
    else {
      const bool enabled = object_item->type() != keyword::camera_object;
      ui_.delete_button->setEnabled(enabled);
      ui_.move_button->setEnabled(enabled);
    }
  };
  connection_list_ <<
      connect(ui_.object_tree, &QTreeWidget::currentItemChanged, enable_button);

  auto edit_name = [this](QTreeWidgetItem* item, const int /* column */)
  {
    auto* object_item = cast<ObjectTreeItem*>(item);
    const auto old_name = object_item->name();
    const auto new_name = item->text(0);
    if (new_name == old_name)
      return;
    object_item->setName(new_name);
  };
  connection_list_ << connect(ui_.object_tree, &QTreeWidget::itemChanged, edit_name);

  auto add_object_item = [this](const char* type, const QString& text)
  {
    auto item = std::unique_ptr<ObjectTreeItem>{new ObjectTreeItem{type}};

    auto add_function = [this](ObjectTreeItem* item)
    {
      ui_.object_tree->addTopLevelItem(item);
      ui_.object_tree->setCurrentItem(nullptr);
    };

    auto take_function = [this]()
    {
      const int count = ui_.object_tree->topLevelItemCount();
      auto* item = 
          cast<ObjectTreeItem*>(ui_.object_tree->takeTopLevelItem(count - 1));
      ui_.object_tree->setCurrentItem(nullptr);
      return item;
    };

    auto* command = 
        new AddObjectCommand<ObjectTreeItem>{text, std::move(item), 
                                             add_function, take_function};

    auto* window = ReflectWidget::mainWindow();
    window->appendCommand(command);
  };

  auto add_single_object_item = [add_object_item]()
  {
    add_object_item(keyword::single_object, "Add a object item.");
  };
  connection_list_ << connectButton(ui_.object_add_button, add_single_object_item);

  auto add_group_item = [add_object_item]()
  {
    add_object_item(keyword::group_object, "Add a group item.");
  };
  connection_list_ << connectButton(ui_.group_add_button, add_group_item);

  auto delete_object = [this]()
  {
    auto* object_item = cast<ObjectTreeItem*>(ui_.object_tree->currentItem());
    auto* parent = (object_item->parent() != nullptr)
        ? object_item->parent()
        : ui_.object_tree->invisibleRootItem();
    const auto text = QStringLiteral("Delete object \"%1\".").arg(object_item->name());
    const int index = parent->indexOfChild(object_item);
    auto take_function = [this, parent, index]()
    {
      auto* item =  cast<ObjectTreeItem*>(parent->takeChild(index));
      ui_.object_tree->setCurrentItem(nullptr);
      return item;
    };

    auto add_function = [this, parent, index](ObjectTreeItem* item)
    {
      parent->insertChild(index, item);
      ui_.object_tree->setCurrentItem(nullptr);
    };

    auto* command = 
        new DeleteObjectCommand<ObjectTreeItem>{text, take_function, add_function};

    auto* window = ReflectWidget::mainWindow();
    window->appendCommand(command);
  };
  connection_list_ << connectButton(ui_.delete_button, delete_object);

  auto enable_non_group_object = [this](const bool enabled,
                                        ObjectTreeItem* selected_object)
  {
    QList<QTreeWidgetItem*> group_list;
    group_list.append(ui_.object_tree->invisibleRootItem());
    for (int i = 0; i < group_list.size(); ++i) {
      auto* group = group_list.at(i);
      group->setDisabled(false);
      for (int index = 0; index < group->childCount(); ++index) {
        auto* child = cast<ObjectTreeItem*>(group->child(index));
        if (child != selected_object && child->type() == keyword::group_object)
          group_list.append(child);
        else
          child->setDisabled(!enabled);
      }
    }
  };

  auto set_move_mode = [this, enable_non_group_object](const bool flag)
  {
    is_object_move_mode_ = flag;

    // Other widgets
    auto* window = cast<ReflectMainWindow*>(ReflectWidget::mainWindow());
    for (auto* widget : window->childWidgets())
      widget->setEnabled(!flag);
    window->object_view->setEnabled(true);
    window->object_setting_frame->setEnabled(!flag);
    window->object_frame->setEnabled(true);

    // Some buttons
    ui_.object_add_button->setEnabled(!flag);
    ui_.group_add_button->setEnabled(!flag);
    ui_.delete_button->setEnabled(!flag);
    ui_.cancel_button->setEnabled(flag);

    // A selected object and non group objects
    auto* selected_object = flag
        ? cast<ObjectTreeItem*>(ui_.object_tree->currentItem())
        : nullptr;
    enable_non_group_object(!flag, selected_object);
    ui_.object_tree->setEditTriggers( flag
        ? QAbstractItemView::NoEditTriggers
        : QAbstractItemView::DoubleClicked);
  };

  auto move_object = [this, enable_button, set_move_mode]()
  {
    if (!isObjectMoveMode()) {
      set_move_mode(true);
      selected_object_ = ui_.object_tree->currentItem();
      ui_.object_tree->setCurrentItem(nullptr);
    }
    else {
      auto* source = (selected_object_->parent() == nullptr)
          ? ui_.object_tree->invisibleRootItem()
          : selected_object_->parent();
      auto* destination = ui_.object_tree->currentItem();
      const auto text = QStringLiteral("Move \"%1\" to \"%2\".").arg(
          selected_object_->text(0), destination->text(0));
      const int index = source->indexOfChild(selected_object_);
      auto function1 = [this, source, destination, index]()
      {
        auto* item = source->takeChild(index);
        destination->addChild(item);
        ui_.object_tree->setCurrentItem(nullptr);
      };
      auto function2 = [this, source, destination, index]()
      {
        const int count = destination->childCount();
        auto* item = destination->takeChild(count - 1);
        source->insertChild(index, item);
        ui_.object_tree->setCurrentItem(nullptr);
      };
      auto* command = new FunctionCommand{text, function1, function2};
      auto* window = ReflectWidget::mainWindow();
      window->appendCommand(command);

      set_move_mode(false);
      enable_button(nullptr, nullptr);
      cast<ReflectTreeItem*>(selected_object_)->deactivate();
      selected_object_ = nullptr;
    }
  };
  connection_list_ << connectButton(ui_.move_button, move_object);

  auto set_edit_move = [this, enable_button, set_move_mode]()
  {
    set_move_mode(false);
    selected_object_ = nullptr;
    ui_.object_tree->setCurrentItem(nullptr);
    enable_button(nullptr, nullptr);
  };
  connection_list_ << connectButton(ui_.cancel_button, set_edit_move);

  auto call_move_object = [this, move_object]()
  {
    if (isObjectMoveMode() && ui_.move_button->isEnabled())
      move_object();
  };
  connection_list_ <<
      connect(ui_.object_tree, &QTreeWidget::itemDoubleClicked, call_move_object);

  auto* camera_item = new ObjectTreeItem{keyword::camera_object};
  ui_.object_tree->addTopLevelItem(camera_item);
  ui_.object_tree->setCurrentItem(camera_item);
}

} // namespace reflect
