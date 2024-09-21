cmake_minimum_required(VERSION 3.0)

## Add C++ build flags
#macro(AddCxxFlags)
#  foreach(flag ${ARGN})
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
#  endforeach()
#endmacro(AddCxxFlags)


## GCC configuration
macro(InitializeGccForCxx11)
  # Version check
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8.0)
    message(FATAL_ERROR "Use GCC version 4.8 or later.")
  endif()
  # Add Compile options
  add_compile_options(-std=c++11)
endmacro(InitializeGccForCxx11)


## Clang configuration
macro(InitializeClangForCxx11)
  # Version check
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.2.0)
    message(FATAL_ERROR "Use Clang version 3.2 or later.")
  endif()
  # Add Compile options
  add_compile_options(-std=c++11)
  if(z_mac)
    add_compile_options(-stdlib=libc++)
  endif()
endmacro(InitializeClangForCxx11)


## Initialize C++ compiler options
macro(InitializeForCxx11)
  if(z_gcc)
    InitializeGccForCxx11()
  elseif(z_clang)
    InitializeClangForCxx11()
  # TODO: Add new compiler initialization
  else()
    message(FATAL_ERROR "\"${CMAKE_CXX_COMPILER_ID}\" doesn't support C++11")
  endif()
endmacro(InitializeForCxx11)


## GCC configuration
macro(InitializeGccForCxx14)
  # Version check
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.0)
    message(FATAL_ERROR "Use GCC version 4.9 or later.")
  endif()
  # Add Compile options
  add_compile_options(-std=c++14)
endmacro(InitializeGccForCxx14)


## Clang configuration
macro(InitializeClangForCxx14)
  # Version check
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5.0)
    message(FATAL_ERROR "Use Clang version 3.5 or later.")
  endif()
  # Add Compile options
  add_compile_options(-std=c++14)
  if(z_mac)
    add_compile_options(-stdlib=libc++)
  endif()
endmacro(InitializeClangForCxx14)


## Initialize C++ compiler options
macro(InitializeForCxx14)
  if(z_gcc)
    InitializeGccForCxx14()
  elseif(z_clang)
    InitializeClangForCxx14()
  # TODO: Add new compiler initialization
  else()
    message(FATAL_ERROR "\"${CMAKE_CXX_COMPILER_ID}\" doesn't support C++14")
  endif()
endmacro(InitializeForCxx14)


## Set C++ warning flags
macro(EnableWarningForCxx)
  if(z_gcc OR z_clang)
    add_compile_options(-Wall -Wextra)
  else()
    message(WARNING "\"${CMAKE_CXX_COMPILER_ID}\" doesn't support worning option.")
  endif()
endmacro(EnableWarningForCxx)  
