/*!
  \file material_list_manager.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_LIST_MANAGER_HPP_
#define _REFLECT_MATERIAL_LIST_MANAGER_HPP_

// Qt
#include <QObject>

// Forward declaration
class QComboBox;
class QString;
class QVariant;

namespace reflect {

/*!
  \details
  No detailed.
  */
class MaterialListManager : public QObject
{
  Q_OBJECT

 signals:
  //! This signal is called when list item is deleted
  void listItemDeleted(const int index) const;

  //! This signal is called when list item is edited
  void listItemEdited(const int index, const QString& text) const;

  //! This signal is called when list item is inserted
  void listItemInserted(const int index, const QString& text) const;
};

//! Update a combobox
void updateDeletedItem(const int index, QVariant& value, QComboBox* combobox);

//! Update a combobox
void updateEditedItem(const int index, const QString& text, QComboBox* combobox);

//! Update a combobox
void updateInsertedItem(const int index, const QString& text,
                        QVariant& value, QComboBox* combobox);

} // namespace reflect

#endif // _REFLECT_MATERIAL_LIST_MANAGER_HPP_
