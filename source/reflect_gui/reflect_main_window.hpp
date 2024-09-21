/*!
  \file reflect_main_window.hpp
  \author takemura
  */

#ifndef _REFLECT_REFLECT_MAIN_WINDOW_HPP_
#define _REFLECT_REFLECT_MAIN_WINDOW_HPP_

// Qt
#include <QList>
#include <QString>
// Zisc
#include "zisc/thread_pool.hpp"
// ReflectGui
#include "reflect_widget.hpp"
// UI
#include "ui_main_window.h"

// Forward declaration
class BsdfWidget;
class LightWidget;
class QSettings;
class QStringList;
class QUndoStack;
class QUndoView;
class QWidget;

namespace reflect {

// Forward declaration
class ReflectCommand;
class RendererManager;
struct ReflectOptions;

/*!
  \details
  No detailed.
  */
class ReflectMainWindow : public ReflectWidget, public Ui::MainWindow
{
  Q_OBJECT

 public:
  //! Create main window
  ReflectMainWindow(const ReflectOptions& options);

  //! Finalize main window
  ~ReflectMainWindow();


  //! Append a command to the command stack
  void appendCommand(ReflectCommand* command);

  //! Get all child widgets
  QList<QWidget*> childWidgets() const;

  //! Disable command logging
  void disableCommandLogging();

  //! Return the light widget pointer
  const ReflectWidget* emitterModelWidget() const;

  //! Enable command logging
  void enableCommandLogging();

  //! Get speficied file path
  QString getOpenFilePath(const QString& caption,
                          const QString& directory,
                          const QString& filter);

  //! Check whether command logging is enabled
  bool isEnabledCommandLogging() const;

  //! Load setting file
  void loadSetting(const QString& file_path);

  //! Save setting file
  void saveSetting(const QString& file_path) const;

  //! Save setting file
  void saveSetting(QSettings* settings) const;

  //! Return the bsdf widget pointer
  const ReflectWidget* surfaceModelWidget() const;

  //! Return the texture widget pointer
  const ReflectWidget* textureWidget() const;

  //! Validate data
  void validateData(QStringList* error_message_list) const override;

 public slots:
  //! Print message
  void printMessage(const QString& message) const;

  //! Display image
  void showImage(const QImage& image) const;

 private:
  //! Initialize
  void initialize();

  //! Initialize command log view
  void initializeCommandLogView();

  //! Initialize operation buttons
  void initializeOperationButton();

  //! Initialize text browser
  void initializeTextBrowser();

  //! Set default settings
  void setDefaultConfiguration(QSettings* settings) const;

  //! Set default property setting
  void setDefaultProperty(QSettings* settings) const;


  bool is_enabled_command_logging_;
  // Setting tabs
  ReflectWidget* bvh_widget_;
  ReflectWidget* color_widget_;
  ReflectWidget* rendering_method_widget_;
  ReflectWidget* system_widget_;
  // Material
  ReflectWidget* emitter_model_widget_;
  ReflectWidget* surface_model_widget_;
  ReflectWidget* texture_widget_;
  // Object
  ReflectWidget* object_tree_;
  // Command log
  QUndoStack* command_stack_;
  QUndoView* command_log_view_;
  // Renderer
  const ReflectOptions* options_;
  RendererManager* renderer_manager_;
  zisc::ThreadPool renderer_thread_;
};

} // namespace reflect

#endif // _REFLECT_REFLECT_MAIN_WINDOW_HPP_
