/*!
  \file rotation_item.cpp
  \author takemura
  */

#include "rotation_item.hpp"
// Standard C++ library
#include <functional>
// Qt
#include <QDoubleSpinBox>
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "widget_connection.hpp"



namespace reflect {

 /*!
  \details
  No detailed.
  */
RotationItem::RotationItem()
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void RotationItem::initializeLayerFrame(QWidget* frame)
{
  resetConnection();
  if (!item_widget_.isNull())
    delete item_widget_;

  item_widget_ = new QWidget{frame};
  ui_.setupUi(item_widget_);

  ui_.axis_combobox->addItem(keyword::x_axis);
  ui_.axis_combobox->addItem(keyword::y_axis);
  ui_.axis_combobox->addItem(keyword::z_axis);
  auto set_axis = [this](const int index)
  {
    constexpr auto key = keyword::axis;
    const auto current_text = ui_.axis_combobox->itemText(index);
    table_[key].setValue(current_text);
  };
  ui_.axis_combobox->setCurrentText(table_[keyword::axis].toString());
  connection_list_ << connectComboBox(ui_.axis_combobox, set_axis);

  auto set_angle = [this](const double angle)
  {
    constexpr auto key = keyword::angle;
    table_[key].setValue(angle);
  };
  ui_.angle_spinbox->setValue(table_[keyword::angle].toDouble());
  connection_list_ << connectSpinBox(ui_.angle_spinbox, set_angle);

  ui_.unit_combobox->addItem(keyword::degree_unit);
  ui_.unit_combobox->addItem(keyword::radian_unit);
  auto set_angle_unit = [this](const int index)
  {
    constexpr auto key = keyword::angle_unit;
    const auto current_text = ui_.unit_combobox->itemText(index);
    table_[key].setValue(current_text);
  };
  ui_.unit_combobox->setCurrentText(table_[keyword::angle_unit].toString());
  connection_list_ << connectComboBox(ui_.unit_combobox, set_angle_unit);
}

/*!
  \details
  No detailed.
  */
void RotationItem::initialize()
{
  setName(keyword::rotation);
  table_[keyword::axis].setValue(QString{keyword::x_axis});
  table_[keyword::angle].setValue(0.0);
  table_[keyword::angle_unit].setValue(QString{keyword::degree_unit});
}

/*!
  \details
  No detailed.
  */
void RotationItem::readLayerData(const QString& prefix,
                                 const QSettings& settings)
{
  auto key = prefix + "/" + keyword::axis;
  const auto axis = settings.value(key, QString{keyword::x_axis});
  ui_.axis_combobox->setCurrentText(axis.toString());

  key = prefix + "/" + keyword::angle;
  const auto angle = settings.value(key, 0.0);
  ui_.angle_spinbox->setValue(angle.toDouble());

  key = prefix + "/" + keyword::angle_unit;
  const auto angle_unit = settings.value(key, QString{keyword::degree_unit});
  ui_.unit_combobox->setCurrentText(angle_unit.toString());
}

} // namespace reflect
