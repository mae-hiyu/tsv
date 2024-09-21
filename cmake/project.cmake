cmake_minimum_required(VERSION 3.0)


macro(SetProjectProperties)
  set(reflect_version ${PROJECT_VERSION})
  set(reflect_version_major ${PROJECT_VERSION_MAJOR})
  set(reflect_version_minor ${PROJECT_VERSION_MINOR})
  set(reflect_version_patch ${PROJECT_VERSION_PATCH})

  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  #  set(CMAKE_AUTOMOC ON)
endmacro(SetProjectProperties)


macro(SetLibraries)
  ## Load libraries
  # OpenCL
  set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
  #find_package(OpenCL 1.2)
  #if(OpenCL_FOUND)
  #  set(enable_reflect_opencl TRUE)
  #  make_directory(${PROJECT_BINARY_DIR}/OpenCL)
  #  add_definitions(-DREFLECT_OPENCL)
  #  include_directories(${OpenCL_INCLUDR_DIRS})
  #  # For debug
  #  message(STATUS "## OpenCL found. version: ${OpenCL_VERSION_STRING}")
  #else()
  #  set(enable_reflect_opencl FALSE)
  #  # For debug
  #  message(STATUS "## OpenCL found. version: ${OpenCL_VERSION_STRING}")
  #endif()
  set(enable_reflect_opencl FALSE)
  
  # Qt
  include(${PROJECT_SOURCE_DIR}/cmake/qt5.cmake)
  FindQt5()
  add_definitions(${qt5_definitions})
  include_directories(${qt5_include_dirs})
  SetQtUiFiles()
  include_directories(${ui_include_dir})
  SetQtResources()
  
  # Zisc
  include(${PROJECT_SOURCE_DIR}/source/zisc/config.cmake)
  LoadZisc()
  include_directories(${zisc_include_dirs})
  
  ## Load and set source files
  # ReflectCore
  include(${PROJECT_SOURCE_DIR}/source/reflect_core/config.cmake)
  SetReflectCore()
  include_directories(${reflect_core_include_dirs})
  # ReflectOpenCL
  if(enable_reflect_opencl)
    include(${PROJECT_SOURCE_DIR}/source/reflect_open_cl/config.cmake)
    SetReflectOpenCl()
    include_directories(${reflect_open_cl_include_dirs})
  endif()
  # ReflectRenderer
  include(${PROJECT_SOURCE_DIR}/source/reflect_renderer/config.cmake)
  SetReflectRenderer()
  include_directories(${reflect_renderer_include_dir})
  # ReflectGui
  include(${PROJECT_SOURCE_DIR}/source/reflect_gui/config.cmake)
  SetReflectGui()
  include_directories(${reflect_gui_include_dir})


  ## Set library properties
  file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/libs)

  set(__reflect_libs__ ${reflect_core_library} ${reflect_gui_library}
                       ${reflect_open_cl_library} ${reflect_renderer_library})
  set_target_properties(${__reflect_libs__} PROPERTIES
      VERSION ${reflect_version}
      SOVERSION ${reflect_version_major})

  set_target_properties(${zisc_library} ${__reflect_libs__} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libs)
endmacro(SetLibraries)

macro(BuildSizeChecker)
  set(__source_files__ ${PROJECT_SOURCE_DIR}/test/size_checker.cpp)
  add_executable(SizeChecker ${__source_files__})
  target_link_libraries(SizeChecker ${qt5_libraries}
                                    ${zisc_library}
                                    ${reflect_core_library})
endmacro(BuildSizeChecker)
