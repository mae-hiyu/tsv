/*!
  \file replace_widget_command.cpp
  \author takemura
  */

#include "replace_widget_command.hpp"
// Qt
#include <QPointer>
#include <QString>
// ReflectGui
#include "reflect_command.hpp"
#include "reflect_widget.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
ReplaceWidgetCommand::ReplaceWidgetCommand(const QString& text,
                                           ReflectWidget* old_widget,
                                           ReflectWidget* new_widget,
                                           ReflectWidget** current_widget) :
    ReflectCommand(text),
    old_widget_{old_widget},
    new_widget_{new_widget},
    unused_widget_{old_widget},
    current_widget_{current_widget}
{
}

/*!
  \details
  No detailed.
  */
ReplaceWidgetCommand::~ReplaceWidgetCommand()
{
  if (!unused_widget_.isNull())
    delete unused_widget_;
}

/*!
  \details
  No detailed.
  */
void ReplaceWidgetCommand::redoCommand()
{
  if (!old_widget_.isNull())
    old_widget_->deactivate();
  if (!new_widget_.isNull())
    new_widget_->activate();
  unused_widget_ = old_widget_;
  *current_widget_ = new_widget_;
}

/*!
  \details
  No detailed.
  */
void ReplaceWidgetCommand::undoCommand()
{
  if (!new_widget_.isNull())
    new_widget_->deactivate();
  if (!old_widget_.isNull())
    old_widget_->activate();
  unused_widget_ = new_widget_;
  *current_widget_ = old_widget_;
}

} // namespace reflect
