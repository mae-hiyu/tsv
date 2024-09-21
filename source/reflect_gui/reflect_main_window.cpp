/*!
  \file reflect_main_window.cpp
  \author takemura
  */

#include "reflect_main_window.hpp"
// Standard C++ library
#include <functional>
#include <memory>
#include <string>
// Qt
#include <QAbstractSlider>
#include <QDir>
#include <QFileDialog>
#include <QFont>
#include <QList>
#include <QScrollBar>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QUndoStack>
#include <QUndoView>
#include <QWidget>
// Zisc
#include "zisc/error.hpp"
// ReflectCore
#include "keyword.hpp"
#include "RendererBase/renderer_base.hpp"
#include "RendererBase/renderer_manager.hpp"
// ReflectRenderer
#include "reflect_options.hpp"
#include "renderer.hpp"
// ReflectGui
#include "reflect_widget.hpp"
#include "widget_connection.hpp"
#include "BasicSettings/bvh_widget.hpp"
#include "BasicSettings/color_widget.hpp"
#include "BasicSettings/rendering_method_widget.hpp"
#include "BasicSettings/system_widget.hpp"
#include "Command/reflect_command.hpp"
#include "MaterialWidget/material_widget.hpp"
#include "ObjectWidget/object_tree.hpp"
#include "Utility/value.hpp"
#ifdef REFLECT_OPENCL
#include "OpenCL/cl_renderer.hpp"
#endif // REFLECT_OPENCL
// UI
#include "ui_main_window.h"

namespace reflect {

/*!
  \details
  No detailed.
  */
ReflectMainWindow::ReflectMainWindow(const ReflectOptions& options) :
    ReflectWidget(nullptr),
    options_{&options},
    renderer_thread_{1}
{
  initialize();
}

/*!
  \details
  No detailed.
  */
ReflectMainWindow::~ReflectMainWindow()
{
  setMainWindows(nullptr);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::appendCommand(ReflectCommand* command)
{
  command_stack_->push(command);
}

/*!
  \details
  No detailed.
  */
QList<QWidget*> ReflectMainWindow::childWidgets() const
{
  return findChildren<QWidget*>(QString{}, Qt::FindDirectChildrenOnly);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::disableCommandLogging()
{
  is_enabled_command_logging_ = false;
}

/*!
  \details
  No detailed.
  */
const ReflectWidget* ReflectMainWindow::emitterModelWidget() const
{
  return emitter_model_widget_;
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::enableCommandLogging()
{
  is_enabled_command_logging_ = true;
}

/*!
  \details
  No detailed.
  */
QString ReflectMainWindow::getOpenFilePath(const QString& caption,
                                           const QString& directory,
                                           const QString& filter)
{
  const auto file_path = 
      QFileDialog::getOpenFileName(this, caption, directory, filter);
  if (file_path.isEmpty())
    return file_path;
  QDir current_directory;
  return current_directory.relativeFilePath(file_path);
}

/*!
  \details
  No detailed.
  */
bool ReflectMainWindow::isEnabledCommandLogging() const
{
  return is_enabled_command_logging_;
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::loadSetting(const QString& file_path)
{
  // Clear command log
  command_stack_->clear();

  // Load a setting file
  QSettings settings{file_path, QSettings::IniFormat};

  disableCommandLogging();

  // Basic settings
  system_widget_->readData(keyword::system_group, settings);
  color_widget_->readData(keyword::color_group, settings);
  rendering_method_widget_->readData(keyword::rendering_method_group, settings);
  bvh_widget_->readData(keyword::bvh_group, settings);

  // Material
  texture_widget_->readData(keyword::texture, settings);
  surface_model_widget_->readData(keyword::surface_model, settings);
  emitter_model_widget_->readData(keyword::emitter_model, settings);

  // Objects
  object_tree_->readData(keyword::object, settings);

  enableCommandLogging();
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::saveSetting(const QString& file_path) const
{
  QSettings settings{file_path, QSettings::IniFormat};
  saveSetting(&settings);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::saveSetting(QSettings* settings) const
{
  settings->clear();

  // Basic settings
  system_widget_->writeData(keyword::system_group, settings);
  color_widget_->writeData(keyword::color_group, settings);
  rendering_method_widget_->writeData(keyword::rendering_method_group, settings);
  bvh_widget_->writeData(keyword::bvh_group, settings);

  // Material
  texture_widget_->writeData(keyword::texture, settings);
  surface_model_widget_->writeData(keyword::surface_model, settings);
  emitter_model_widget_->writeData(keyword::emitter_model, settings);

  // Objects
  object_tree_->writeData(keyword::object, settings);

  // Default settings
  setDefaultConfiguration(settings);
}

/*!
  \details
  No detailed.
  */
const ReflectWidget* ReflectMainWindow::surfaceModelWidget() const
{
  return surface_model_widget_;
}

/*!
  \details
  No detailed.
  */
const ReflectWidget* ReflectMainWindow::textureWidget() const
{
  return texture_widget_;
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::validateData(QStringList* error_message_list) const
{
  // Validate data of basic settings
  system_widget_->validateData(error_message_list);
  color_widget_->validateData(error_message_list);
  rendering_method_widget_->validateData(error_message_list);
  bvh_widget_->validateData(error_message_list);

  // Material
  texture_widget_->validateData(error_message_list);
  surface_model_widget_->validateData(error_message_list);
  emitter_model_widget_->validateData(error_message_list);

  // Validate object data
  object_tree_->validateData(error_message_list);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::printMessage(const QString& message) const
{
  message_log_view->appendPlainText(message);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::showImage(const QImage& image) const
{
  const auto pixmap = QPixmap::fromImage(image);
  const auto image_size = pixmap.size();
  const auto view_size = image_view->size();
  if ((image_size.width() <= view_size.width()) && 
      (image_size.height() <= view_size.height()))
    image_view->setPixmap(pixmap.copy());
  else
    image_view->setPixmap(pixmap.scaled(view_size, Qt::KeepAspectRatio));
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::initialize()
{
  setMainWindows(this);

  setupUi(this);

  is_enabled_command_logging_ = false;

  disableCommandLogging();

  // Initialize setting tab
  system_widget_ = new SystemWidget{system_frame};
  color_widget_ = new ColorWidget{color_frame};
  rendering_method_widget_ = new RenderingMethodWidget{rendering_method_frame};
  bvh_widget_ = new BvhWidget{bvh_frame};

  // Material
  emitter_model_widget_ = new EmitterModelWidget{emitter_model_frame};
  surface_model_widget_ = new SurfaceModelWidget{surface_model_frame};
  texture_widget_ = new TextureWidget{texture_frame};

  // Object
  object_tree_ = new ObjectTree{object_frame};
  
  initializeCommandLogView();
  initializeOperationButton();
  initializeTextBrowser();

  enableCommandLogging();
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::initializeCommandLogView()
{
  command_stack_ = new QUndoStack{this};
  command_stack_->setUndoLimit(50);
  command_log_view_ = new QUndoView{command_stack_, command_log_frame};
  command_log_view_->setGeometry(
      0, 0, command_log_frame->width(), command_log_frame->height());
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::initializeOperationButton()
{
  // Undo button
  undo_button->setEnabled(false);
  connect(command_stack_, SIGNAL(canUndoChanged(bool)),
          undo_button, SLOT(setEnabled(bool)));
  connect(undo_button, SIGNAL(clicked()), command_stack_, SLOT(undo()));

  // Redo button
  redo_button->setEnabled(false);
  connect(command_stack_, SIGNAL(canRedoChanged(bool)),
          redo_button, SLOT(setEnabled(bool)));
  connect(redo_button, SIGNAL(clicked()), command_stack_, SLOT(redo()));

  // Load button
  auto load_settings = [this]()
  {
    const QString caption{"Load setting file"};
    const QString filter{"ReflectFile (*.refl)"};
    const auto file_path = getOpenFilePath(caption, ".", filter);
    if (!file_path.isEmpty())
      loadSetting(file_path);
  };
  connectButton(load_button, load_settings);

  // Save button
  auto save_settings = [this]()
  {
    const QString caption{"Save setting file"};
    const QString filter{"ReflectFile (*.refl)"};
    const auto file_path = QFileDialog::getSaveFileName(this, caption, ".", filter);
    if (!file_path.isEmpty())
      saveSetting(file_path);
  };
  connectButton(save_button, save_settings);

  auto set_rendering_mode = [this](const bool enabled)
  {
    for (auto& widget : childWidgets())
      widget->setEnabled(!enabled);
    image_view->setEnabled(true);
    message_log_view->setEnabled(true);
    gridLayoutWidget->setEnabled(true);
    undo_button->setEnabled(enabled ? false : command_stack_->canUndo());
    redo_button->setEnabled(enabled ? false : command_stack_->canRedo());
    load_button->setEnabled(!enabled);
    save_button->setEnabled(!enabled);
    render_button->setEnabled(!enabled);
    stop_button->setEnabled(enabled);
  };

  auto render = [this, set_rendering_mode](const QString rendering_dir)
  {
    // Save settings
    QSettings settings{rendering_dir + "/scene.refl", QSettings::IniFormat};
    saveSetting(&settings);
    settings.sync();

    const auto key = QString{keyword::system_group} + "/" + keyword::open_cl;
    const bool enable_open_cl = value<bool>(settings, key);

    std::unique_ptr<RendererBase> renderer;
#ifdef REFLECT_OPENCL
    if (enable_open_cl)
      renderer.reset(new ClRenderer{settings});
    else
      renderer.reset(new Renderer{settings});
#else // REFLECT_OPENCL
    renderer.reset(new Renderer{settings});
#endif // REFLECT_OPENCL
    auto& manager = renderer->manager();
    renderer_manager_ = &manager;

    manager.setRenderingDirectory(rendering_dir);

    connect(&manager, SIGNAL(outputText(const QString&)), 
            this, SLOT(printMessage(const QString&)));

    connect(&manager, SIGNAL(outputImage(const QImage&)),
            this, SLOT(showImage(const QImage&)));

    connect(&manager, 
            &RendererManager::finishedRendering, 
            std::bind(set_rendering_mode, false));

    renderer->initialize(settings);

    renderer->render();
  };

  auto start_rendering = [this, set_rendering_mode, render]()
  {
    // Show a separator
    printMessage("----------------------------------------");

    // Data validation
    QStringList error_message_list;
    validateData(&error_message_list);
    if (!error_message_list.isEmpty()) {
      for (const auto& error_message : error_message_list)
        printMessage(QStringLiteral("## Error: ") + error_message);
      return;
    }

    // Diactivate some widgets
    set_rendering_mode(true);

    // Make rendering directory
    QDir output_dir{options_->output_dir_};
    const auto rendering_dir_name = 
        cast<SystemWidget*>(system_widget_)->sceneName() + "_" +
        RendererBase::getCurrentTime();
    output_dir.mkdir(rendering_dir_name);
    const auto rendering_dir = options_->output_dir_ + "/" + rendering_dir_name;

    // Render scene
    printMessage("Initialize renderer.");
    std::function<void ()> render_scene{std::bind(render, rendering_dir)};
    renderer_thread_.enqueue(std::move(render_scene));
  };
  connectButton(render_button, start_rendering);

  auto stop_rendering = [this]()
  {
    renderer_manager_->finishRendering();
  };
  connectButton(stop_button, stop_rendering);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::initializeTextBrowser()
{
  auto is_auto_scroll_mode = std::make_shared<bool>(true);
  auto* text_scroll_bar = message_log_view->verticalScrollBar();

  auto set_auto_scroll = 
  [this, is_auto_scroll_mode, text_scroll_bar](const int value)
  {
    *is_auto_scroll_mode = (value == text_scroll_bar->maximum());
  };
  connect(text_scroll_bar, &QAbstractSlider::valueChanged, set_auto_scroll);

  auto auto_scroll = 
  [this, is_auto_scroll_mode, text_scroll_bar](const int /* min */, const int max)
  {
    if (*is_auto_scroll_mode)
      text_scroll_bar->setValue(max);
  };
  connect(text_scroll_bar, &QAbstractSlider::rangeChanged, auto_scroll);
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::setDefaultConfiguration(QSettings* settings) const
{
  const QString group{keyword::default_setting};
  settings->beginGroup(group);

  EmitterModelWidget::setDefaultConfiguration(QString{keyword::emitter_model}, 
                                              settings);
  SurfaceModelWidget::setDefaultConfiguration(QString{keyword::surface_model}, 
                                              settings);
  TextureWidget::setDefaultConfiguration(QString{keyword::texture}, settings);

  setDefaultProperty(settings);

  settings->endGroup();
}

/*!
  \details
  No detailed.
  */
void ReflectMainWindow::setDefaultProperty(QSettings* settings) const
{
  const QString group{keyword::property};
  settings->beginGroup(group);

  QString key;

  key = keyword::type;
  settings->setValue(key, QString{keyword::spectra});

  key = keyword::spectra_file;
  settings->setValue(key, QString{":/property/white.csv"});

  settings->endGroup();
}

} // namespace reflect
