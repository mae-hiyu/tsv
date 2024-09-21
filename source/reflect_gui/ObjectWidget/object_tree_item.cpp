/*!
  \file object_tree_item.cpp
  \author takemura
  */

#include "object_tree_item.hpp"
// Qt
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "camera_object_widget.hpp"
#include "group_object_widget.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "single_object_widget.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
ObjectTreeItem::ObjectTreeItem(const char* type) :
    type_{type}
{
  initialize(type);
}

/*!
  \details
  No detailed.
  */
ObjectTreeItem::~ObjectTreeItem()   
{
  if (!item_widget_.isNull())
    delete item_widget_;
}

/*!
  \details
  No detailed.
  */
void ObjectTreeItem::activate()
{
  item_widget_->activate();
}

/*!
  \details
  No detailed.
  */
void ObjectTreeItem::deactivate()
{
  item_widget_->deactivate();
}

/*!
  \details
  No detailed.
  */
void ObjectTreeItem::readData(const QString& prefix, 
                              const QSettings& settings)
{
  auto key = prefix + "/" + keyword::name;
  const auto name = settings.value(key).toString();
  setName(name);

  if (type() == keyword::group_object) {
    key = prefix + "/" + keyword::count;
    const int count = settings.value(key).toInt();
    for (int index = 0; index < count; ++index) {
      const auto object_id = prefix + "/" + QString{keyword::item}.arg(index);
      key = object_id + "/" + keyword::type;
      const auto object_type = settings.value(key).toString();
      auto* object_item = new ObjectTreeItem{object_type.toStdString().c_str()};
      object_item->readData(object_id, settings);
      addChild(object_item);
    }
  }

  item_widget_->readData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
const QString& ObjectTreeItem::type() const
{
  return type_;
}

/*!
  \details
  No detailed.
  */
void ObjectTreeItem::validateData(QStringList* error_message_list) const
{
  item_widget_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void ObjectTreeItem::writeData(const QString& prefix, QSettings* settings) const
{
  writeTableData(prefix, settings);

  if (type() == keyword::group_object) {
    const int count = childCount();
    const auto key = prefix + "/" + keyword::count;
    settings->setValue(key, count);
    for (int index = 0; index < count; ++index) {
      auto* object_item = cast<ObjectTreeItem*>(child(index));
      const auto object_id = prefix + "/" + QString{keyword::item}.arg(index);
      object_item->writeData(object_id, settings);
    }
  }

  item_widget_->writeData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ObjectTreeItem::initialize(const char* type)
{
  auto* window = ReflectWidget::mainWindow();

  setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);

  switch (zisc::toHash32(type)) {
   case zisc::toHash32(keyword::camera_object):
    setName("Camera");
    item_widget_ = new CameraObjectWidget{window->object_setting_frame};
    break;
   case zisc::toHash32(keyword::group_object):
    setName("Group");
    item_widget_ = new GroupObjectWidget{window->object_setting_frame};
    break;
   case zisc::toHash32(keyword::single_object):
    setName("Object");
    item_widget_ = new SingleObjectWidget{window->object_setting_frame};
    break;
   default:
    zisc::raiseError("ObjectError: Unsupported type is specified.");
    break;
  }
  table_[keyword::type].setValue(QString{type});
}

} // namespace reflect
