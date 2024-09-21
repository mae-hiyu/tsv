/*!
  \file spectrum_palette_widget.cpp
  \author takemura
  */

#include "spectrum_palette_widget.hpp"
// Qt
#include <QFileInfo>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/utility.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
// UI
#include "ui_spectrum_palette_widget.h"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SpectrumPaletteWidget::SpectrumPaletteWidget(QWidget* parent) :
    ReflectWidget(parent)
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void SpectrumPaletteWidget::readData(const QString& prefix, 
                                     const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::spectra_file;
  const auto file_path = settings.value(key, QString{}).toString();
  if (!file_path.isEmpty()) {
    table_[keyword::spectra_file].setValue(file_path);
    const QFileInfo file_info{file_path};
    ui_.open_spectra_file_button->setText(file_info.fileName());
  }
}

/*!
  \details
  No detailed.
  */
void SpectrumPaletteWidget::setText(const QString& text)
{
  ui_.open_spectra_file_button->setText(text);
}

/*!
  \details
  No detailed.
  */
void SpectrumPaletteWidget::validateData(QStringList* error_message_list) const
{
  const auto file_path = table_[keyword::spectra_file].toString();
  const QFileInfo file_info{file_path};
  if (!file_info.exists()) {
    const auto error_message = 
        QStringLiteral("SpectrumPaletteWidget: Spectra file \"%1\" is not exist.");
    (*error_message_list) << error_message.arg(file_path);
  }
}

/*!
  \details
  No detailed.
  */
void SpectrumPaletteWidget::initialize()
{
  ui_.setupUi(this);

  auto set_spectra_file = [this](const QString& file_path)
  {
    table_[keyword::spectra_file].setValue(file_path);
    const QFileInfo file_info{file_path};
    ui_.open_spectra_file_button->setText(file_info.fileName());
  };

  auto open_spectra_file = [this, set_spectra_file]()
  {
    const QString caption{"Open spectra file"};
    const QString directory{"../properties"};
    const QString filter{"Spectra file (*.csv)"};
    auto* window = ReflectWidget::mainWindow();
    const auto file_path = window->getOpenFilePath(caption, directory, filter);
    if (!file_path.isEmpty())
      set_spectra_file(file_path);
  };
  connection_list_ << connectButton(ui_.open_spectra_file_button, open_spectra_file);
}

} // namespace reflect
