/*!
  \file group_object_widget.cpp
  \author takemura
  */

#include "group_object_widget.hpp"
// Qt
#include <QCheckBox>
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "TransformationWidget/transformation_widget.hpp"
// UI
#include "ui_group_item_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
GroupObjectWidget::GroupObjectWidget(QWidget* parent) :
  ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void GroupObjectWidget::readData(const QString& prefix, 
                                 const QSettings& settings)
{
  auto key = prefix + "/" + keyword::visibility;
  const auto visibility = settings.value(key, true);
  ui_.visibility_checkbox->setChecked(visibility.toBool());

  key = prefix + "/" + keyword::transformation;
  transformation_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void GroupObjectWidget::writeData(const QString& prefix, QSettings* settings) const
{
  writeTableData(prefix, settings);
  const auto key = prefix + "/" + keyword::transformation;
  transformation_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void GroupObjectWidget::initialize()
{
  ui_.setupUi(this);

  transformation_widget_ = new TransformationWidget{ui_.transformation_frame};

  auto set_visibility = [this](const bool visibility)
  {
    constexpr auto key = keyword::visibility;
    table_[key].setValue(visibility);
  };
  connection_list_ << connectCheckBox(ui_.visibility_checkbox, set_visibility);
  set_visibility(ui_.visibility_checkbox->isChecked());
}

} // namespace reflect
