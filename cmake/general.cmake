cmake_minimum_required(VERSION 3.0)

## Make file cleaner scripts
function(MakeCleanerScript)
  file(WRITE ${PROJECT_BINARY_DIR}/clean_all_files.sh
       "rm -rf ${PROJECT_BINARY_DIR}/*")
  file(WRITE ${PROJECT_BINARY_DIR}/clean_cmake_files.sh
       "rm -rf ${PROJECT_BINARY_DIR}/CMakeCache.txt ${PROJECT_BINARY_DIR}/CMakeFiles ${PROJECT_BINARY_DIR}/cmake_install.cmake")
endfunction(MakeCleanerScript)


## Prohibit building on all directories except debug and release directory.
macro(RestrictBuildDirectory)
  set(__build_directory__ "${PROJECT_SOURCE_DIR}/build")
  if(NOT PROJECT_BINARY_DIR MATCHES "${__build_directory__}(/*)?")
    message(FATAL_ERROR "\"${PROJECT_BINARY_DIR}\" dir is not allowed to build.\n"
                        "Please build on \"${__build_directory__}\".")
  endif()
endmacro(RestrictBuildDirectory)


## Set build type
macro(SetBuildType)
  # Build type
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
  endif()
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(z_debug ON)
    add_definitions(-DZ_DEBUG)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(z_release ON)
    add_definitions(-DZ_RELEASE)
  else()
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
  endif()
  message(STATUS "## Build type: ${CMAKE_BUILD_TYPE}")
endmacro(SetBuildType)


## Detect platform
macro(DetectPlatform)
  # Detect OS
  if(WIN32)
    set(z_windows ON)
    add_definitions(-DZ_WINDOWS)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(z_linux ON)
    add_definitions(-DZ_LINUX)
  elseif(APPLE)
    set(z_mac ON)
    add_definitions(-DZ_MAC)
  else()
    message(WARNING "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
  endif()
  message(STATUS "## System: ${CMAKE_SYSTEM_NAME}")

  # Detect C++ compiler
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(z_gcc ON)
    add_definitions(-DZ_GCC)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR 
         CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(z_clang ON)
    add_definitions(-DZ_CLANG)
  else()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
  endif()
  message(STATUS "## Compiler: ${CMAKE_CXX_COMPILER_ID}")

  # Detect environment
  if(CMAKE_GENERATOR MATCHES ".*Makefiles")
    set(z_makefile ON)
    set(z_cui ON)
  elseif (CMAKE_GENERATOR STREQUAL "Xcode")
    set(z_xcode ON)
    set(z_ide ON)
  else()
    message(WARNING "Unsupported environment: ${CMAKE_GENERATOR}")
  endif()
  message(STATUS "## Develop environment: ${CMAKE_GENERATOR}")
endmacro(DetectPlatform)


## Initialize
macro(Initialize)
  RestrictBuildDirectory()
  #  MakeCleanerScript()
  SetBuildType()
  DetectPlatform()
endmacro(Initialize)
