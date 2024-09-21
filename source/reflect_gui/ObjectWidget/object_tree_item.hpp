/*!
  \file object_tree_item.hpp
  \author takemura
  */

#ifndef _REFLECT_OBJECT_TREE_ITEM_HPP_
#define _REFLECT_OBJECT_TREE_ITEM_HPP_

// Qt
#include <QPointer>
#include <QString>
// ReflectGui
#include "reflect_widget.hpp"
#include "reflect_widget_item.hpp"

// Forward declaration
class QSettings;
class QStringList;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ObjectTreeItem : public ReflectTreeItem
{
 public:
  //! Create object tree item
  ObjectTreeItem(const char* type);

  //! Delete item widget
  ~ObjectTreeItem();


  //! Show item widget
  void activate() override;

  //! Hide item widget
  void deactivate() override;

  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Get the object type
  const QString& type() const;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 protected:
  //! Initialize
  void initialize(const char* type);


  QPointer<ReflectWidget> item_widget_;
  QString type_;
};

} // namespace reflect

#endif // _REFLECT_OBJECT_TREE_ITEM_HPP_
