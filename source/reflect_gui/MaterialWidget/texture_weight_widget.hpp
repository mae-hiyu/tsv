/*!
  \file texture_weight_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_TEXTURE_WEIGHT_WIDGET_HPP_
#define _REFLECT_TEXTURE_WEIGHT_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_texture_weight_widget.h"

// Forward declaration
class QSettings;
class QString;
class QWidget;

namespace reflect {

/*!
  \details
  No detailed.
  */
class TextureWeightWidget : public ReflectWidget
{
 public:
  //! Create a texture weight widget
  TextureWeightWidget(QWidget* parent);


  //! Read data from a setting file
  void readData(const QString& prefix, const QSettings& settings) override;

 private:
  //! Initialize
  void initialize();

  //! Initialize texture combobox
  void initializeTextureComboBox();


  bool is_updating_;
  Ui::TextureWeightWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_TEXTURE_WEIGHT_WIDGET_HPP_
