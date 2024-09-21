/*!
  \file bvh_widget.cpp
  \author takemura
  */

#include "bvh_widget.hpp"
// Qt
#include <QPointer>
#include <QSettings>
#include <QString>
#include <QWidget>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "Command/replace_widget_command.hpp"
#include "Command/set_value_command.hpp"
#include "BasicSettings/BvhWidget/approximate_agglomerative_clustering_bvh_widget.hpp"
#include "BasicSettings/BvhWidget/binary_radix_bvh_widget.hpp"
#include "BasicSettings/BvhWidget/median_split_bvh_widget.hpp"
// UI
#include "ui_bvh_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
BvhWidget::BvhWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void BvhWidget::readData(const QString& prefix, const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::type;
  const QString default_bvh{keyword::binary_radix_bvh};
  const auto type = settings.value(key, default_bvh);
  ui_.bvh_combobox->setCurrentText(type.toString());

  if (ui_.bvh_combobox->currentText() != type.toString())
    ui_.bvh_combobox->setCurrentText(default_bvh);

  QPointer<ReflectWidget> current_widget{current_widget_};
  if (!current_widget.isNull())
    delete current_widget;
  current_widget_ = makeBvhWidget(ui_.bvh_combobox->currentText());
  current_widget_->readData(prefix, settings);
  current_widget_->activate();
}

/*!
  \details
  No detailed.
  */
void BvhWidget::writeData(const QString& prefix, QSettings* settings) const
{
  writeTableData(prefix, settings);
  current_widget_->writeData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void BvhWidget::initialize()
{
  ui_.setupUi(this);

  ui_.bvh_combobox->addItem(keyword::binary_radix_bvh);
  ui_.bvh_combobox->addItem(keyword::median_split_bvh);
  ui_.bvh_combobox->addItem(keyword::approximate_agglomerative_clustering_bvh);
  ui_.bvh_combobox->setCurrentText(keyword::median_split_bvh);

  auto update_bvh_type = [this](const QString& type)
  {
    ui_.bvh_combobox->setCurrentText(type);
  };

  auto set_bvh = [this, update_bvh_type](const int type)
  {
    constexpr auto key = keyword::type;
    auto window = ReflectWidget::mainWindow();
    const auto new_bvh = ui_.bvh_combobox->itemText(type);
    if (window->isEnabledCommandLogging()) {
      const auto text = QStringLiteral("Set bvh to \"%1\".").arg(new_bvh);
      const auto old_bvh = table_[key].toString();
      auto command = new SetValueCommand<QString>{text, new_bvh, 
                                                  old_bvh, update_bvh_type};

      auto old_widget = current_widget_;
      window->disableCommandLogging();
      auto new_widget = makeBvhWidget(new_bvh);
      auto child = new ReplaceWidgetCommand{"", old_widget, 
                                            new_widget, &current_widget_};
      command->addChild(child);

      window->appendCommand(command);
    }
    table_[key].setValue(new_bvh);
  };

  connectComboBox(ui_.bvh_combobox, set_bvh);
  set_bvh(ui_.bvh_combobox->currentIndex());
  current_widget_ = makeBvhWidget(ui_.bvh_combobox->currentText());
}

/*!
  \details
  No detailed.
  */
ReflectWidget* BvhWidget::makeBvhWidget(const QString& type)
{
  ReflectWidget* bvh_widget = nullptr;

  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::binary_radix_bvh):
    bvh_widget = new BinaryRadixBvhWidget{ui_.bvh_frame};
    break;
   case zisc::toHash32(keyword::median_split_bvh):
    bvh_widget = new MedianSplitBvhWidget{ui_.bvh_frame};
    break;
   case zisc::toHash32(keyword::approximate_agglomerative_clustering_bvh):
    bvh_widget = new ApproximateAgglomerativeClusteringBvhWidget{ui_.bvh_frame};
    break;
   default:
    zisc::raiseError("BvhError: Unsupported bvh is specified.");
    break;
  }

  return bvh_widget;
}

} // namespace reflect
