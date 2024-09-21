cmake_minimum_required(VERSION 3.0.0)

# Defined variables
#   qt5_definitions:
#   qt5_include_dirs: 
#   qt5_libraries: 
#   qt5_root_dir: 
macro(FindQt5)
  # QtCore
  find_package(Qt5Core 5.3 REQUIRED)
  set(qt5_definitions ${qt5_definitions} ${Qt5Core_DEFINITIONS})
  set(qt5_include_dirs ${qt5_include_dirs} ${Qt5Core_INCLUDE_DIRS})
  set(qt5_libraries ${qt5_libraries} ${Qt5Core_LIBRARIES})

  # QtGui
  find_package(Qt5Gui 5.3 REQUIRED)
  set(qt5_definitions ${qt5_definitions} ${Qt5Gui_DEFINITIONS})
  set(qt5_include_dirs ${qt5_include_dirs} ${Qt5Gui_INCLUDE_DIRS})
  set(qt5_libraries ${qt5_libraries} ${Qt5Gui_LIBRARIES})

  # QtWidgets
  find_package(Qt5Widgets 5.3 REQUIRED)
  set(qt5_definitions ${qt5_definitions} ${Qt5Widgets_DEFINITIONS})
  set(qt5_include_dirs ${qt5_include_dirs} ${Qt5Widgets_INCLUDE_DIRS})
  set(qt5_libraries ${qt5_libraries} ${Qt5Widgets_LIBRARIES})

  # Set other variables
  get_target_property(__qt5_core_location__ ${Qt5Core_LIBRARIES} LOCATION)
  get_filename_component(__qt5_core_dir__ ${__qt5_core_location__} DIRECTORY)
  get_filename_component(__qt5_lib_dir__ ${__qt5_core_dir__} DIRECTORY)
  get_filename_component(qt5_root_dir ${__qt5_lib_dir__} DIRECTORY)

  # For debug
  #  message(STATUS "## Qt5Core definitions: ${Qt5Core_DEFINITIONS}")
  #  message(STATUS "## Qt5Core include dirs: ${Qt5Core_INCLUDE_DIRS}")
  #  message(STATUS "## Qt5Core libraries: ${Qt5Core_LIBRARIES}")
  #  message(STATUS "## Qt5Gui definitions: ${Qt5Gui_DEFINITIONS}")
  #  message(STATUS "## Qt5Gui include dirs: ${Qt5Gui_INCLUDE_DIRS}")
  #  message(STATUS "## Qt5Gui libraries: ${Qt5Gui_LIBRARIES}")
  #  message(STATUS "## Qt5Widgets definitions: ${Qt5Widgets_DEFINITIONS}")
  #  message(STATUS "## Qt5Widgets include dirs: ${Qt5Widgets_INCLUDE_DIRS}")
  #  message(STATUS "## Qt5Widgets libraries: ${Qt5Widgets_LIBRARIES}")
  #  message(STATUS "## Qt5 root dir: ${qt5_root_dir}")
endmacro(FindQt5)

# Defined variables
#   ui_include_dir:
#   reflect_ui_hpp_files: 
macro(SetQtUiFiles)
  file(GLOB __ui_files__ ${PROJECT_SOURCE_DIR}/ui/*.ui)

  set(ui_include_dir ${PROJECT_BINARY_DIR}/include/ui)
  file(MAKE_DIRECTORY ${ui_include_dir})
  set(__current_binary_dir__ ${CMAKE_CURRENT_BINARY_DIR})
  set(CMAKE_CURRENT_BINARY_DIR ${ui_include_dir})

  qt5_wrap_ui(reflect_ui_hpp_files ${__ui_files__})
  source_group(ReflectGui\\Ui FILES ${reflect_ui_hpp_files})

  set(CMAKE_CURRENT_BINARY_DIR ${__current_binary_dir__})
endmacro(SetQtUiFiles)

# Defined variables
#   reflect_resource_files:
macro(SetQtResources)
  set(__resource_dir__ ${PROJECT_BINARY_DIR}/resource)
  file(MAKE_DIRECTORY ${__resource_dir__})
  set(__current_binary_dir__ ${CMAKE_CURRENT_BINARY_DIR})
  set(CMAKE_CURRENT_BINARY_DIR ${__resource_dir__})

  qt5_add_resources(reflect_resource_files ${PROJECT_SOURCE_DIR}/resource.qrc)
  source_group(ReflectCore\\Resource FILES ${reflect_resource_files})

  set(CMAKE_CURRENT_BINARY_DIR ${__current_binary_dir__})
endmacro(SetQtResources)
