/*!
  \file replace_widget_command.hpp
  \author takemura
  */

#ifndef _REFLECT_REPLACE_WIDGET_COMMAND_HPP_
#define _REFLECT_REPLACE_WIDGET_COMMAND_HPP_

// Qt
#include <QPointer>
// ReflectGui
#include "reflect_command.hpp"
#include "reflect_widget.hpp"

// Forward declaration
class QString;

namespace reflect {

/*!
  \details
  No detailed.
  */
class ReplaceWidgetCommand : public ReflectCommand
{
 public:
  //! Create replace widget command
  ReplaceWidgetCommand(const QString& text, 
                       ReflectWidget* old_widget,
                       ReflectWidget* new_widget,
                       ReflectWidget** current_widget);

  //! Delete unused widget
  ~ReplaceWidgetCommand();


  //! Execute redo
  void redoCommand() override;

  //! Execute undo
  void undoCommand() override;

 private:
  QPointer<ReflectWidget> old_widget_,
                          new_widget_;
  QPointer<ReflectWidget> unused_widget_;
  ReflectWidget** current_widget_;
};

} // namespace reflect

#endif // _REFLECT_REPLACE_WIDGET_COMMAND_HPP_
