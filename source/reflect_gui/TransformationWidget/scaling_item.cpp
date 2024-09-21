/*!
  \file scaling_item.cpp
  \author takemura
  */

#include "scaling_item.hpp"
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
ScalingItem::ScalingItem()
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ScalingItem::initializeLayerFrame(QWidget* frame)
{
  resetConnection();
  if (!item_widget_.isNull())
    delete item_widget_;

  item_widget_ = new QWidget{frame};
  ui_.setupUi(item_widget_);

  auto set_value = [this](const QString& key, const double value)
  {
    table_[key].setValue(value);
  };
  QString key{keyword::x};
  connection_list_ << 
      connectSpinBox(ui_.x_spinbox, 
                     std::bind(set_value, key, std::placeholders::_1));
  key = keyword::y;
  connection_list_ << 
      connectSpinBox(ui_.y_spinbox, 
                     std::bind(set_value, key, std::placeholders::_1));
  key = keyword::z;
  connection_list_ << 
      connectSpinBox(ui_.z_spinbox, 
                     std::bind(set_value, key, std::placeholders::_1));

  ui_.x_spinbox->setValue(table_[keyword::x].toDouble());
  ui_.y_spinbox->setValue(table_[keyword::y].toDouble());
  ui_.z_spinbox->setValue(table_[keyword::z].toDouble());
}

/*!
  \details
  No detailed.
  */
void ScalingItem::initialize()
{
  setName(keyword::scaling);
  table_[keyword::x].setValue(1.0);
  table_[keyword::y].setValue(1.0);
  table_[keyword::z].setValue(1.0);
}

/*!
  \details
  No detailed.
  */
void ScalingItem::readLayerData(const QString& prefix,
                                const QSettings& settings)
{
  auto key = prefix + "/" + keyword::x;
  const auto x = settings.value(key, 1.0);
  ui_.x_spinbox->setValue(x.toDouble());

  key = prefix + "/" + keyword::y;
  const auto y = settings.value(key, 1.0);
  ui_.y_spinbox->setValue(y.toDouble());

  key = prefix + "/" + keyword::z;
  const auto z = settings.value(key, 1.0);
  ui_.z_spinbox->setValue(z.toDouble());
}

} // namespace reflect
