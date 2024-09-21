/*!
  \file thin_film_item.hpp
  \author takemura
  */

#ifndef _REFLECT_THIN_FILM_ITEM_HPP_
#define _REFLECT_THIN_FILM_ITEM_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_layer.hpp"
#include "reflect_widget.hpp"
// UI
#include "ui_thin_film_widget.h"

// Forward declaration
class QSettings;
class QString;
class QStringList;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ThinFilmItem : public ReflectLayer
{
 public:
  //! Create a thin film layer widget
  ThinFilmItem();

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();

  //! Initialize layer frame
  void initializeLayerFrame(QWidget* frame) override;

  //! Read layer data from a setting file
  void readLayerData(const QString& prefix, const QSettings& settings) override;


  QPointer<QWidget> item_widget_;
  ReflectWidget* refractive_index_widget_;
  ReflectWidget* extinction_widget_;
  Ui::ThinFilmWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_THIN_FILM_ITEM_HPP_
