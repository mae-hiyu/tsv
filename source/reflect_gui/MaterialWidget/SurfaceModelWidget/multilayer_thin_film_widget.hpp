/*!
  \file multilayer_thin_film_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_MULTILAYER_THIN_FILM_WIDGET_HPP_
#define _REFLECT_MULTILAYER_THIN_FILM_WIDGET_HPP_

// ReflectGui
#include "reflect_multilayer.hpp"
#include "reflect_widget.hpp"
// UI
#include "ui_multilayer_thin_film_widget.h"

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
class MultilayerThinFilmWidget : public ReflectMultilayer
{
 public:
  //! Create a multilayer thin film widget
  MultilayerThinFilmWidget(QWidget* parent);


  //! Read data to a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

  //! Write data to a setting file
  void writeData(const QString& prefix, QSettings* settings) const override;

 private:
  //! Initialize
  void initialize();


  ReflectWidget* exterior_refractive_index_widget_;
  ReflectWidget* interior_refractive_index_widget_;
  ReflectWidget* interior_extinction_widget_;
  Ui::MultilayerThinFilmWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_MULTILAYER_THIN_FILM_WIDGET_HPP_
