cmake_minimum_required(VERSION 3.0.0)


set(__zisc_path__ ${CMAKE_CURRENT_LIST_DIR})

# Defined variables
#   zisc_include_dirs:
#   zisc_library:
macro(LoadZisc)
  ## Set version information
  set(zisc_version_major 0)
  set(zisc_version_minor 5)
  set(zisc_version_patch 0)
  set(zisc_version "${zisc_version_major}.${zisc_version_minor}.${zisc_version_patch}")
  message(STATUS "## Zisc version: ${zisc_version}")
  
  
  ## Make configuration header file
  set(__zisc_config_path__ ${PROJECT_BINARY_DIR}/include/zisc)
  configure_file(${__zisc_path__}/zisc/zisc_config.hpp.in
                 ${__zisc_config_path__}/zisc_config.hpp)
  
  ## Set dependencies
  if (z_linux)
    set(__zisc_dependencies__ pthread)
  endif()
  
  ## Set source code
  file(GLOB __zisc_cpp_files__ ${__zisc_path__}/zisc/*.cpp)
  file(GLOB __zisc_hpp_files__ ${__zisc_path__}/zisc/*.hpp)
  set(__zisc_hpp_files__ ${__zisc_hpp_files__} ${__zisc_config_path__}/zisc_config.hpp)
  source_group(Zisc FILES ${__zisc_cpp_files__} ${__zisc_hpp_files__})
  add_library(Zisc SHARED ${__zisc_cpp_files__} ${__zisc_hpp_files__})
  target_link_libraries(Zisc ${__zisc_dependencies__})

  # Set properties
  set_target_properties(Zisc PROPERTIES 
      VERSION ${zisc_version}
      SOVERSION ${zisc_version_major})

  ## Set variables 
  set(zisc_include_dirs ${__zisc_path__} ${PROJECT_BINARY_DIR}/include)
  set(zisc_library Zisc)
endmacro()
