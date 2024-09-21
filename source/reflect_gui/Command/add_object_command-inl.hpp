/*!
  \file add_object_command-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_ADD_OBJECT_COMMAND_INL_HPP_
#define _REFLECT_ADD_OBJECT_COMMAND_INL_HPP_

#include "add_object_command.hpp"
// Standard C++ library
#include <functional>
#include <memory>
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
template <typename Type> inline
AddObjectCommand<Type>::AddObjectCommand(
    const QString& text,
    std::unique_ptr<Type>&& object,
    std::function<void (Type*)> add_function,
    std::function<Type* ()> take_function) :
        ReflectCommand(text),
        object_{std::move(object)},
        add_function_{std::move(add_function)},
        take_function_{std::move(take_function)}
{
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void AddObjectCommand<Type>::redoCommand()
{
  add_function_(object_.release());
}

/*!
  \details
  No detailed.
  */
template <typename Type> inline
void AddObjectCommand<Type>::undoCommand()
{
  object_.reset(take_function_());
}

} // namespace reflect

#endif // _REFLECT_ADD_OBJECT_COMMAND_INL_HPP_
