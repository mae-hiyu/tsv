/*!
  \file texture_weight_widget.cpp
  \author takemura
  */

#include "texture_weight_widget.hpp"
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/error.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "MaterialWidget/material_widget.hpp"
#include "MaterialWidget/material_list_manager.hpp"
// UI
#include "ui_texture_weight_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
TextureWeightWidget::TextureWeightWidget(QWidget* parent) :
    ReflectWidget(parent),
    is_updating_{false}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void TextureWeightWidget::readData(const QString& prefix, 
                                   const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::texture_index;
  const auto texture_index = settings.value(key, 0);
  ui_.texture_combobox->setCurrentIndex(texture_index.toInt());
}

/*!
  \details
  No detailed.
  */
void TextureWeightWidget::initialize()
{
  ui_.setupUi(this);

  initializeTextureComboBox();
}

/*!
  \details
  No detailed.
  */
void TextureWeightWidget::initializeTextureComboBox()
{
  const auto* window = cast<ReflectMainWindow*>(ReflectWidget::mainWindow());
  const auto* texture_widget = cast<const TextureWidget*>(window->textureWidget());
  const auto* texture_list = texture_widget->materialListWidget();

  ui_.texture_combobox->clear();
  ui_.texture_combobox->addItem(keyword::default_type);
  const int count = texture_list->count();
  for (int index = 0; index < count; ++index) {
    const auto* item = texture_list->item(index);
    ui_.texture_combobox->addItem(item->text());
  }
  ui_.texture_combobox->setCurrentIndex(0);

  table_[keyword::texture_index].setValue(0);
  auto set_texture_index = [this](const int type)
  {
    if (is_updating_)
      return;

    constexpr auto key = keyword::texture_index;
    table_[key].setValue(type);
  };
  connection_list_ << connectComboBox(ui_.texture_combobox, set_texture_index);

  const auto* texture_manager = texture_widget->manager();
  auto update_deleted_texture_item = [this](const int index)
  {
    is_updating_ = true;
    auto& value = table_[keyword::texture_index];
    updateDeletedItem(index, value, ui_.texture_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(texture_manager, 
                              &MaterialListManager::listItemDeleted,
                              update_deleted_texture_item);

  auto update_edited_texture_item = [this](const int index,
                                           const QString& text)
  {
    is_updating_ = true;
    updateEditedItem(index, text, ui_.texture_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(texture_manager,
                              &MaterialListManager::listItemEdited,
                              update_edited_texture_item);

  auto update_inserted_texture_item = [this](const int index,
                                             const QString& text)
  {
    is_updating_ = true;
    auto& value = table_[keyword::texture_index];
    updateInsertedItem(index, text, value, ui_.texture_combobox);
    is_updating_ = false;
  };
  connection_list_ << connect(texture_manager,
                              &MaterialListManager::listItemInserted,
                              update_inserted_texture_item);
}

} // namespace reflect
