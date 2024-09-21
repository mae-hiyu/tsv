/*!
  \file function_command.cpp
  \author takemura
  */

#include "function_command.hpp"
// Standard C++ library
#include <functional>
#include <utility>
// ReflectGui
#include "reflect_command.hpp"

// Forward declaration
class QString;

namespace reflect {

/*!
  \details
  No detailed.
  */
FunctionCommand::FunctionCommand(const QString& text,
                                 std::function<void ()> function1,
                                 std::function<void ()> function2) :
    ReflectCommand(text),
    function1_{std::move(function1)},
    function2_{std::move(function2)}
{
}

/*!
  \details
  No detailed.
  */
void FunctionCommand::redoCommand()
{
  function1_();
}

/*!
  \details
  No detailed.
  */
void FunctionCommand::undoCommand()
{
  function2_();
}

} // namespace reflect
