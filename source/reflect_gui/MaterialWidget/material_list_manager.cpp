/*!
  \file material_list_manager.cpp
  \author takemura
  */

#include "material_list_manager.hpp"
// Qt
#include <QComboBox>
#include <QString>
#include <QVariant>

namespace reflect {

/*!
  \details
  No detailed.
  */
void updateDeletedItem(const int index, QVariant& value, QComboBox* combobox)
{
  int item_index = value.toInt();
  if (index < item_index) {
    --item_index;
    value.setValue(item_index);
  }
  combobox->removeItem(index + 1);
  combobox->setCurrentIndex(item_index);
}

/*!
  \details
  No detailed.
  */
void updateEditedItem(const int index, const QString& text, QComboBox* combobox)
{
  combobox->setItemText(index + 1, text);
}

/*!
  \details
  No detailed.
  */
void updateInsertedItem(const int index, const QString& text,
                        QVariant& value, QComboBox* combobox)
{
  int item_index = value.toInt();
  if (index < item_index) {
    ++item_index;
    value.setValue(item_index);
  }
  combobox->insertItem(index + 1, text);
  combobox->setCurrentIndex(item_index);
}

} // namespace reflect
