/*!
  \file unique_pointer.hpp
  \author takemura
  */

#ifndef _REFLECT_UNIQUE_POINTER_HPP_
#define _REFLECT_UNIQUE_POINTER_HPP_

namespace reflect {

//! \addtogroup Utility
//! \{

/*!
  \details
  No detailed.
  */
template <typename Type>
class UniquePointer
{
 public:
  //! Create a empty pointer
  UniquePointer();

  //! Create a unique pointer
  UniquePointer(Type* pointer);

  //! Receive the pointer from a another unique pointer
  UniquePointer(UniquePointer&& pointer);

  //! Delete the managed object
  ~UniquePointer();


  //! Access to the object
  Type& operator*();

  //! Access to the object
  const Type& operator*() const;

  //! Access to the object pointer
  Type* operator->();

  //! Access to the object pointer
  const Type* operator->() const;

  //! It is same as calling reset(pointer)
  UniquePointer& operator=(Type* pointer);

  //! Move the pointer
  UniquePointer& operator=(UniquePointer&& pointer);


  //! Return a pointer to the managed object 
  Type* get();

  //! Return a pointer to the managed object 
  const Type* get() const;

  //! Check if there is not associated managed object
  bool isNull() const;

  //! Replace the managed object
  void reset(Type* pointer = nullptr);

  //! Swap the managed objects with another
  void swap(UniquePointer& pointer);

 private:
  Type* pointer_;
};

//! Compare the pointer
template <typename Type>
bool operator<(const UniquePointer<Type>& a, const UniquePointer<Type>& b);
  
//! \} Utility

} // namespace reflect

#include "unique_pointer-inl.hpp"

#endif // _REFLECT_UNIQUE_POINTER_HPP_
