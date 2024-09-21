/*!
  \file material_item_widget-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_ITEM_WIDGET_INL_HPP_
#define _REFLECT_MATERIAL_ITEM_WIDGET_INL_HPP_

#include "material_item_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "material_item_type.hpp"
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "Command/set_value_command.hpp"
#include "Command/replace_widget_command.hpp"

namespace reflect {

using zisc::cast;  

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
MaterialItemWidget<kType>::MaterialItemWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItemWidget<kType>::readData(const QString& prefix,
                                         const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::type;
  const auto type = settings.value(key).toString();
  ui_.material_type_combobox->setCurrentText(type);
  delete current_widget_;
  current_widget_ = makeMaterialItemWidget<kType>(ui_.material_type_frame, type);
  current_widget_->readData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItemWidget<kType>::validateData(QStringList* error_message_lsit) const
{
  current_widget_->validateData(error_message_lsit);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType> inline
void MaterialItemWidget<kType>::writeData(const QString& prefix,
                                          QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::type;
  settings->setValue(key, table_[keyword::type]);
  current_widget_->writeData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
template <MaterialItemType kType>
void MaterialItemWidget<kType>::initialize()
{
  ui_.setupUi(this);

  ui_.material_type_combobox->addItems(getMaterialTypeList<kType>());
  ui_.material_type_combobox->setCurrentIndex(0);

  auto update_material_type = [this](const QString& type)
  {
    ui_.material_type_combobox->setCurrentText(type);
  };

  auto set_material_type = [this, update_material_type](const int type)
  {
    constexpr auto key = keyword::type;
    auto* window = ReflectWidget::mainWindow();
    const auto new_type = ui_.material_type_combobox->itemText(type);
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set type to \"%1\".").arg(new_type);
      const auto old_type = table_[key].toString();
      auto* command = new SetValueCommand<QString>{text, new_type, old_type,
                                                   update_material_type};

      auto* old_widget = current_widget_;
      window->disableCommandLogging();
      auto* new_widget = 
          makeMaterialItemWidget<kType>(ui_.material_type_frame, new_type);
      window->enableCommandLogging();
      auto* child = 
          new ReplaceWidgetCommand{"", old_widget, new_widget, &current_widget_};
      command->addChild(child);

      window->appendCommand(command);
    }
    table_[key].setValue(new_type);
  };
  connection_list_ << connectComboBox(ui_.material_type_combobox, set_material_type);
  set_material_type(ui_.material_type_combobox->currentIndex());
  current_widget_ = 
      makeMaterialItemWidget<kType>(ui_.material_type_frame, 
                                    ui_.material_type_combobox->currentText());
}

} // namespace reflect

#endif // _REFLECT_MATERIAL_ITEM_WIDGET_INL_HPP_
