/*!
  \file group_object_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_GROUP_OBJECT_WIDGET_HPP_
#define _REFLECT_GROUP_OBJECT_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_group_item_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

// Forward declaration
class TransformationWidget;

/*!
  \details
  No detailed.
  */
class GroupObjectWidget : public ReflectWidget
{
 public:
  //! Create group object item widget
  GroupObjectWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  TransformationWidget* transformation_widget_;
  Ui::GroupItemWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_GROUP_OBJECT_WIDGET_HPP_
