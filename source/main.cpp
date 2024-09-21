/*!
 \file main.cpp
 \author takemura
 */


// Standard C++ library
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

// Qt
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
#include <QFontDatabase>
#include <QString>
#include <QStringList>
#include <QStyleFactory>
#include <QWidget>
// Zisc
#include "zisc/error.hpp"
// ReflectCore
#include "reflect_config.hpp"
// ReflectGui
#include "reflect_main_window.hpp"
// ReflectRenderer
#include "reflect_options.hpp"



//! Process command options
reflect::ReflectOptions processOptions(QApplication& application);

/*!
  \details
  No detailed.
  */
int main(int argc, char** argv)
{
  // Initialize application
  QApplication application{argc, argv};
  QApplication::setApplicationName(kReflectName);
  QApplication::setApplicationVersion(kReflectVersion);
  const auto options = processOptions(application);
  // Make output directory
  QDir output_dir{options.output_dir_};
  if (!output_dir.exists()) {
    const bool result = output_dir.mkpath(".");
    if (!result) {
      const auto message = options.output_dir_ + " is invalid as output directory.";
      zisc::raiseError(message.toStdString());
    }
  }



  // Initialize GUI settings
//  application.setStyle(QStyleFactory::create("Fusion"));

  // Set default font
//  QFontDatabase::addApplicationFont(":/font/Ubuntu-R.ttf");
//  QFontDatabase::addApplicationFont(":/font/Ubuntu-B.ttf");
//  QFontDatabase database;
//  auto font = database.font("Ubuntu", "Regular", 10);
//  application.setFont(font);

  reflect::ReflectMainWindow main_window{options};

   // UI color
  // QPalette mainPal(main_window.palette());
  // mainPal.setColor(QPalette::Background, QColor("#FF0000"));
  // main_window.setPalette(mainPal);
  // main_window.autoFillBackground(true);
  // auto color = main_window.palette().color(QPalette::Background);
  // std::cout << color.red() << std::endl;
  // std::cout << color.blue() << std::endl;
  // std::cout << color.green() << std::endl;
  main_window.show();
  application.exec();
  return 0;
}


/*!
  \details
  No detailed.
  */
reflect::ReflectOptions processOptions(QApplication& application)
{
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();

  const auto description = QStringLiteral(
      "Reflect is a global illumination renderer.");
  parser.setApplicationDescription(description);


  // Options
  QCommandLineOption working_directory_option{
      QStringList{} << "wdir" << "working_dir",
      "Set working directory."};
  parser.addOption(working_directory_option);

  QCommandLineOption output_directory_option{
      QStringList{} << "odir" << "output_dir",
      "Set output directory (working directory is set as default output directory)."};
  parser.addOption(output_directory_option);

  QCommandLineOption style_list_option{
      QStringList{} << "slist" << "style-list",
      "Print supported UI style list."};
  parser.addOption(style_list_option);

  QCommandLineOption style_option{
      QStringList{} << "s" << "style",
      "Specify UI style (default style is \"Fusion\").",
      "",
      "Fusion"};
  parser.addOption(style_option);


  parser.process(application);

  reflect::ReflectOptions options;

  // Set working directory
  if (parser.isSet(working_directory_option))
    QDir::setCurrent(parser.value(working_directory_option));

  // Set output directory
  if (parser.isSet(output_directory_option))
    options.output_dir_ = parser.value(output_directory_option);
  else
    options.output_dir_ = QDir::currentPath();

  // Print style list
  if (parser.isSet(style_list_option)) {
    auto style_list = QStyleFactory::keys();
    std::cout << "Style list" << std::endl;
    for (std::size_t i = 0; i < static_cast<std::size_t>(style_list.size()); ++i) {
      const auto& style = style_list[i];
      std::cout << "  " << style.toStdString() << std::endl;
    }
    std::exit(EXIT_SUCCESS);
  }

  // Set UI style
  const auto style = parser.value(style_option);
  application.setStyle(QStyleFactory::create(style));

  return options;
}

