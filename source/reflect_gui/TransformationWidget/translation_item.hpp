/*!
  \file translation_item.hpp
  \author takemura
  */

#ifndef _REFLECT_TRANSLATION_ITEM_HPP_
#define _REFLECT_TRANSLATION_ITEM_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_layer.hpp"
// UI
#include "ui_translation_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class TranslationItem : public ReflectLayer  
{
 public:
  //! Create a translation item
  TranslationItem();

 private:
  //! Initialize
  void initialize();

  //! Initialize layer frame
  void initializeLayerFrame(QWidget* frame) override;

  //! Read layer data from a setting file
  void readLayerData(const QString& prefix,
                     const QSettings& settings) override;


  QPointer<QWidget> item_widget_;
  Ui::TranslationWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_TRANSLATION_ITEM_HPP_
