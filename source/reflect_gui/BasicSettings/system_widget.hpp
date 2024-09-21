/*!
  \file system_widget.hpp
  \author takemura
  */

#ifndef _REFLECT_SYSTEM_WIDGET_HPP_
#define _REFLECT_SYSTEM_WIDGET_HPP_

// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_system_widget.h"

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
class SystemWidget : public ReflectWidget
{
 public:
  //! Create frame
  SystemWidget(QWidget* parent);


  //! Read data from setting file
  void readData(const QString& prefix, const QSettings& settings) override;

  //! Return the scene name
  QString sceneName() const;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

 private:
  //! Initialize
  void initialize();

  
  Ui::SystemWidget ui_;
};

} // namespace reflect

#endif // _REFLECT_SYSTEM_WIDGET_HPP_
