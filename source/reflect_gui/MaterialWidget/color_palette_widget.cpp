/*!
  \file color_palette_widget.cpp
  \author takemura
  */

#include "color_palette_widget.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
#include <vector>
// Qt
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QWidget>
// Zisc
#include "zisc/error.hpp"
// ReflectCore
#include "keyword.hpp"
// ReflectGui
#include "rgb_palette_widget.hpp"
#include "reflect_widget.hpp"
#include "spectrum_palette_widget.hpp"
#include "widget_connection.hpp"
// UI
#include "ui_color_palette_widget.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ColorPaletteWidget::ColorPaletteWidget(QWidget* parent) :
    ReflectWidget(parent),
    current_palette_{nullptr}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
void ColorPaletteWidget::readData(const QString& prefix, 
                                  const QSettings& settings)
{
  const auto key = prefix + "/" + keyword::type;
  const auto type = settings.value(key, QString{keyword::rgb});
  const std::size_t index = getCurrentIndex(type.toString());
  setCurrentIndex(index);

  current_palette_->readData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
void ColorPaletteWidget::validateData(QStringList* error_message_list) const
{
  current_palette_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void ColorPaletteWidget::writeData(const QString& prefix, QSettings* settings) const
{
  const auto key = prefix + "/" + keyword::type;
  settings->setValue(key, table_[keyword::type]);

  current_palette_->writeData(prefix, settings);
}

/*!
  \details
  No detailed.
  */
std::size_t ColorPaletteWidget::getCurrentIndex(const QString& type) const
{
  for (std::size_t index = 0; index < palette_list_.size(); ++index) {
    if (palette_list_[index].first == type)
      return index;
  }
  zisc::raiseError("ColorPaletteWidgetError: Unsupported type is specified.");
  return 0;
}

/*!
  \details
  No detailed.
  */
void ColorPaletteWidget::initialize()
{
  ui_.setupUi(this);

  palette_list_.emplace_back(QString{keyword::rgb},
                             new RgbPaletteWidget{ui_.palette_frame});
  palette_list_.emplace_back(QString{keyword::spectra},
                             new SpectrumPaletteWidget{ui_.palette_frame});
  for (auto& widget : palette_list_)
    widget.second->deactivate();

  auto change_palette_mode = [this]()
  {
    std::size_t index = getCurrentIndex(ui_.toggle_button->text());
    ++index;
    if (index == palette_list_.size())
      index = 0;
    setCurrentIndex(index);
  };
  connection_list_ << connectButton(ui_.toggle_button, change_palette_mode);
  setCurrentIndex(0);
}

/*!
  \details
  No detailed.
  */
void ColorPaletteWidget::setCurrentIndex(const std::size_t index)
{
  if (current_palette_ != nullptr)
    current_palette_->deactivate();

  ui_.toggle_button->setText(palette_list_[index].first);
  table_[keyword::type] = palette_list_[index].first;
  current_palette_ = palette_list_[index].second;

  current_palette_->activate();
}

} // namespace reflect
