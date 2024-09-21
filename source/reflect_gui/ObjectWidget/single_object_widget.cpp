/*!
  \file single_object_widget.cpp
  \author takemura
  */

#include "single_object_widget.hpp"
// Qt
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
#include "reflect_config.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "MaterialWidget/material_widget.hpp"
#include "MaterialWidget/material_list_manager.hpp"
#include "TransformationWidget/transformation_widget.hpp"
// UI
#include "ui_single_object_item_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SingleObjectWidget::SingleObjectWidget(QWidget* parent) :
    ReflectWidget(parent),
    is_updating_{false}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SingleObjectWidget::readData(const QString& prefix, 
                                  const QSettings& settings)
{
  auto key = prefix + "/" + keyword::visibility;
  const auto visibility = settings.value(key, true);
  ui_.visibility_checkbox->setChecked(visibility.toBool());

  key = prefix + "/" + keyword::geometry_type;
  const auto geometry_type = settings.value(key, QString{keyword::plane_type});
  ui_.geometry_type_combobox->setCurrentText(geometry_type.toString());

  key = prefix + "/" + keyword::object_file;
  const auto object_file = settings.value(key, QString{}).toString();
  if (!object_file.isEmpty()) {
    table_[keyword::object_file].setValue(object_file);
    const QFileInfo file_info{object_file};
    ui_.open_object_file_button->setText(file_info.fileName());
  }

  key = prefix + "/" + keyword::enable_smoothing;
  const auto enabled_smoothing = settings.value(key, true);
  ui_.smoothing_checkbox->setChecked(enabled_smoothing.toBool());

  key = prefix + "/" + keyword::use_nagata_patch;
  const auto use_nagata_patch = settings.value(key, true);
  ui_.nagata_patch_checkbox->setChecked(use_nagata_patch.toBool());

  key = prefix + "/" + keyword::surface_index;
  const auto surface_index = settings.value(key, 0);
  ui_.surface_scattering_combobox->setCurrentIndex(surface_index.toInt());

  key = prefix + "/" + keyword::is_light_source;
  const auto is_light_source = settings.value(key, false);
  ui_.light_source_checkbox->setChecked(is_light_source.toBool());

  key = prefix + "/" + keyword::emitter_index;
  const auto emitter_index = settings.value(key, 0);
  ui_.emitter_combobox->setCurrentIndex(emitter_index.toInt());

  key = prefix + "/" + keyword::transformation;
  transformation_widget_->readData(key, settings);
}

/*!
  \details
  No detailed.
  */
void SingleObjectWidget::validateData(QStringList* error_message_list) const
{
  const bool visibility = table_[keyword::visibility].toBool();
  if (visibility && ((*error_message_list)[0] != keyword::renderable))
    (*error_message_list)[0] = keyword::renderable;

  const bool is_light_source = table_[keyword::is_light_source].toBool();
  if (is_light_source && ((*error_message_list)[1] != keyword::renderable))
    (*error_message_list)[1] = keyword::renderable;

  const auto geometry_type = table_[keyword::geometry_type].toString();
  if (geometry_type == keyword::polygon_type) {
    QDir current_directory;
    const auto object_file = current_directory.relativeFilePath(
        table_[keyword::object_file].toString());
    const QFileInfo file_info{object_file};
    if (!file_info.exists()) {
      const auto error_message = 
          QStringLiteral("Object file \"%1\" is not exist.").arg(object_file);
      (*error_message_list) << error_message;
    }
  }
}

/*!
  \details
  No detailed.
  */
void SingleObjectWidget::writeData(const QString& prefix,
                                   QSettings* settings) const
{
  writeTableData(prefix, settings);
  const auto key = prefix + "/" + keyword::transformation;
  transformation_widget_->writeData(key, settings);
}

/*!
  \details
  No detailed.
  */
void SingleObjectWidget::initialize()
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

  ui_.geometry_type_combobox->addItem(keyword::plane_type);
  ui_.geometry_type_combobox->addItem(keyword::sphere_type);
  ui_.geometry_type_combobox->addItem(keyword::polygon_type);
  ui_.geometry_type_combobox->setCurrentText(keyword::plane_type);
  auto set_geometry_type = [this](const int type)
  {
    constexpr auto key = keyword::geometry_type;
    const auto current_type = ui_.geometry_type_combobox->itemText(type);
    table_[key].setValue(current_type);
    ui_.open_object_file_button->setEnabled(current_type == keyword::polygon_type);
    ui_.polygon_options_box->setEnabled(current_type == keyword::polygon_type);
  };
  connection_list_ << connectComboBox(ui_.geometry_type_combobox, set_geometry_type);
  set_geometry_type(ui_.geometry_type_combobox->currentIndex());

  auto set_object_file = [this](const QString& file_path)
  {
    table_[keyword::object_file].setValue(file_path);
    const QFileInfo file_info{file_path};
    ui_.open_object_file_button->setText(file_info.fileName());
  };

  auto open_object_file = [this, set_object_file]()
  {
    const QString caption{"Open object file"};
    const QString directory{"../models"};
    const QString filter{"Object file (*.obj)"};
    auto* window = ReflectWidget::mainWindow();
    const auto file_path = window->getOpenFilePath(caption, directory, filter);
    if (!file_path.isEmpty())
      set_object_file(file_path);
  };
  connection_list_ << connectButton(ui_.open_object_file_button, open_object_file);

  auto enable_smoothing = [this](const bool enabled)
  {
    constexpr auto key = keyword::enable_smoothing;
    table_[key].setValue(enabled);
    ui_.nagata_patch_checkbox->setEnabled(enabled);
  };
  connection_list_ << connectCheckBox(ui_.smoothing_checkbox, enable_smoothing);
  enable_smoothing(ui_.smoothing_checkbox->isChecked());

  auto enable_nagata_patch = [this](const bool enabled)
  {
    constexpr auto key = keyword::use_nagata_patch;
    table_[key].setValue(enabled);
  };
  connection_list_ << connectCheckBox(ui_.nagata_patch_checkbox, enable_nagata_patch);
  enable_nagata_patch(ui_.nagata_patch_checkbox->isChecked());

  initializeEmitterModelCombobox();
  initializeSurfaceModelCombobox();

  auto enable_light_source = [this](const bool enabled)
  {
    constexpr auto key = keyword::is_light_source;
    table_[key].setValue(enabled);
    ui_.emitter_combobox->setEnabled(enabled);
  };
  connection_list_ << connectCheckBox(ui_.light_source_checkbox, enable_light_source);
  enable_light_source(ui_.light_source_checkbox->isChecked());
}

/*!
  \details
  No detailed.
  */
void SingleObjectWidget::initializeEmitterModelCombobox()
{
  const auto* window = ReflectWidget::mainWindow();
  const auto* emitter_model_widget = 
      cast<const EmitterModelWidget*>(window->emitterModelWidget());
  const auto* emitter_list = emitter_model_widget->materialListWidget();

  ui_.emitter_combobox->clear();
  ui_.emitter_combobox->addItem(keyword::default_type);
  const int count = emitter_list->count();
  for (int index = 0; index < count; ++index) {
    const auto* item = emitter_list->item(index);
    ui_.emitter_combobox->addItem(item->text());
  }
  ui_.emitter_combobox->setCurrentIndex(0);

  table_[keyword::emitter_index].setValue(0);
  auto set_emitter_index = [this](const int type)
  {
    if (is_updating_)
      return;
    constexpr auto key = keyword::emitter_index;
    table_[key].setValue(type);
  };
  connection_list_ << connectComboBox(ui_.emitter_combobox, set_emitter_index);

  const auto* emitter_manager = emitter_model_widget->manager();

  auto update_deleted_emitter_item = [this](const int index)
  {
    is_updating_ = true;
    auto& value = table_[keyword::emitter_index];
    updateDeletedItem(index, value, ui_.emitter_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(emitter_manager, 
                              &MaterialListManager::listItemDeleted,
                              update_deleted_emitter_item);

  auto update_edited_emitter_item = [this](const int index, const QString& text)
  {
    is_updating_ = true;
    updateEditedItem(index, text, ui_.emitter_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(emitter_manager, 
                              &MaterialListManager::listItemEdited,
                              update_edited_emitter_item);

  auto update_inserted_emitter_item = [this](const int index, const QString& text)
  {
    is_updating_ = true;
    auto& value = table_[keyword::emitter_index];
    updateInsertedItem(index, text, value, ui_.emitter_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(emitter_manager, 
                              &MaterialListManager::listItemInserted,
                              update_inserted_emitter_item);
}

/*!
  \details
  No detailed.
  */
void SingleObjectWidget::initializeSurfaceModelCombobox()
{
  const auto* window = ReflectWidget::mainWindow();
  const auto* surface_model_widget = 
      cast<const SurfaceModelWidget*>(window->surfaceModelWidget());
  const auto* surface_scattering_list = surface_model_widget->materialListWidget();

  ui_.surface_scattering_combobox->clear();
  ui_.surface_scattering_combobox->addItem(keyword::default_type);
  const int count = surface_scattering_list->count();
  for (int index = 0; index < count; ++index) {
    const auto* item = surface_scattering_list->item(index);
    ui_.surface_scattering_combobox->addItem(item->text());
  }
  ui_.surface_scattering_combobox->setCurrentIndex(0);

  table_[keyword::surface_index].setValue(0);
  auto set_surface_index = [this](const int type)
  {
    if (is_updating_)
      return;
    constexpr auto key = keyword::surface_index;
    table_[key].setValue(type);
  };
  connection_list_ <<
      connectComboBox(ui_.surface_scattering_combobox, set_surface_index);

  const auto* surface_scattering_manager = surface_model_widget->manager();

  auto update_deleted_surface_scattering_item = [this](const int index)
  {
    is_updating_ = true;
    auto& value = table_[keyword::surface_index];
    updateDeletedItem(index, value, ui_.surface_scattering_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(surface_scattering_manager, 
                              &MaterialListManager::listItemDeleted,
                              update_deleted_surface_scattering_item);

  auto update_edited_surface_scattering_item = [this](const int index,
                                                      const QString& text)
  {
    is_updating_ = true;
    updateEditedItem(index, text, ui_.surface_scattering_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(surface_scattering_manager, 
                              &MaterialListManager::listItemEdited,
                              update_edited_surface_scattering_item);

  auto update_inserted_surface_scattering_item = [this](const int index,
                                                        const QString& text)
  {
    is_updating_ = true;
    auto& value = table_[keyword::surface_index];
    updateInsertedItem(index, text, value, ui_.surface_scattering_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(surface_scattering_manager, 
                              &MaterialListManager::listItemInserted,
                              update_inserted_surface_scattering_item);
}

} // namespace reflect
