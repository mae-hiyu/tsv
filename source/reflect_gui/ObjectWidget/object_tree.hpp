/*!
  \file object_tree.hpp
  \author takemura
  */

#ifndef _REFLECT_OBJECT_TREE_HPP_
#define _REFLECT_OBJECT_TREE_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_widget.hpp"
#include "reflect_widget_item.hpp"
// UI
#include "ui_object_widget.h"

// Forward declaration
class QSettings;
class QString;
class QStringList;
class QTreeWidgetItem;
class QWidget;

namespace reflect {

// Forward declaration
class ObjectTreeItem;

/*!
  \details
  No detailed.
  */
class ObjectTree : public ReflectWidget
{
 public:
  //! Create object tree
  ObjectTree(QWidget* parent);

  //! Delete material widgets
  ~ObjectTree();


  //! Check if the object tree is object move mode
  bool isObjectMoveMode() const;

  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  bool is_object_move_mode_;
  QTreeWidgetItem* selected_object_;
  Ui::ObjectWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_OBJECT_TREE_HPP_
