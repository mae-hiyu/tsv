cmake_minimum_required(VERSION 3.0)


## The project information
project(TSVRenderer VERSION 0.1.0 LANGUAGES C CXX)
message(STATUS "## TSVRenderer version: ${PROJECT_VERSION}")


set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
set(CMAKE_CXX_FLAGS -Wno-inconsistent-missing-override)
include(${PROJECT_SOURCE_DIR}/cmake/project.cmake)
SetProjectProperties()

## Set command options
include(${PROJECT_SOURCE_DIR}/cmake/option.cmake)
SetCommandOptions()
if(REFLECT_FLOAT_CHECK)
  add_definitions(-DREFLECT_FLOAT_CHECK)
endif()

## Build configuration
include(${PROJECT_SOURCE_DIR}/cmake/general.cmake)
Initialize()
include(${PROJECT_SOURCE_DIR}/cmake/compiler.cmake)
InitializeForCxx11()
EnableWarningForCxx()

SetLibraries()

#MakeConfigFiles()
if(REFLECT_BUILD_DOCUMENT)
  include(${PROJECT_SOURCE_DIR}/cmake/document.cmake)
  BuildDocument()
endif()


## Make execution file
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/source/main.cpp 
                               ${reflect_resource_files})
target_link_libraries(${PROJECT_NAME} ${qt5_libraries} 
                                      ${zisc_library}
                                      ${reflect_core_library}
                                      ${reflect_gui_library}
                                      ${reflect_open_cl_library}
                                      ${reflect_renderer_library}
                                      )

## Build extra tools
if(REFLECT_BUILD_EXTRA_TOOLS)
  include(${PROJECT_SOURCE_DIR}/tools/spectra_rmse_calculator/config.cmake)
  BuildSpectraRmseCalculator()
endif()

BuildSizeChecker()
