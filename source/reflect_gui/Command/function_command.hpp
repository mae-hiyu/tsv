/*!
  \file function_command.hpp
  \author takemura
  */

#ifndef _REFLECT_FUNCTION_COMMAND_HPP_
#define _REFLECT_FUNCTION_COMMAND_HPP_

// Standard C++ library
#include <functional>
// ReflectGui
#include "reflect_command.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
class FunctionCommand : public ReflectCommand
{
 public:
  //! Create a function command
  FunctionCommand(const QString& text, 
                  std::function<void ()> function1,
                  std::function<void ()> function2);


  //! Execute redo
  void redoCommand() override;

  //! Execute undo
  void undoCommand() override;

 private:
  std::function<void ()> function1_,
                         function2_;
};

} // namespace reflect

#endif // _REFLECT_FUNCTION_COMMAND_HPP_
