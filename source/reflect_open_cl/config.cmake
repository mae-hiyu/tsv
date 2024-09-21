cmake_minimum_required(VERSION 3.0.0)

set(__reflect_open_cl_path__ ${CMAKE_CURRENT_LIST_DIR})

macro(AddOpenClFiles dir_name)
  file(GLOB __open_cl_cpp_files__ ${__reflect_open_cl_path__}/${dir_name}/*.cpp)
  file(GLOB __open_cl_hpp_files__ ${__reflect_open_cl_path__}/${dir_name}/*.hpp)
  if(NOT "${dir_name}" STREQUAL "")
    string(REPLACE "/" "\\\\" __group_name__ "\\\\${dir_name}")
  endif()
  source_group(ReflectOpenCl${__group_name__} FILES ${__open_cl_cpp_files__} 
                                                    ${__open_cl_hpp_files__})
  set(__open_cl_source_files__ ${__open_cl_source_files__} 
                               ${__open_cl_cpp_files__} 
                               ${__open_cl_hpp_files__})

  file(GLOB __open_cl_cl_files__ ${__reflect_open_cl_path__}/${dir_name}/*.cl)
  file(GLOB __open_cl_h_files__ ${__reflect_open_cl_path__}/${dir_name}/*.h)
  file(COPY ${__open_cl_cl_files__} ${__open_cl_h_files__} 
       DESTINATION ${PROJECT_BINARY_DIR}/OpenCL)

  # For debug
  #  message("## OpenCl name: ${dir_name}")
  #  message("## Group name: ${__group_name__}")
endmacro(AddOpenClFiles)

# Defined variables
#   reflect_open_cl_include_dir:
#   reflect_open_cl_library
macro(SetReflectOpenCl)
  set(__open_cl_config_path__ ${PROJECT_BINARY_DIR}/include/reflect_open_cl)
  make_directory(${__open_cl_config_path__})
  source_group(ReflectOpenCl FILES ${__open_cl_config_path__}/cl_reflect_config.hpp)
  set(__open_cl_source_files__ ${__open_cl_source_files__} 
                               ${__open_cl_config_path__}/cl_reflect_config.hpp)

  set(__open_cl_file_path__ ${PROJECT_BINARY_DIR}/OpenCL)
  make_directory(${__open_cl_file_path__})

  # Generate a config file
  configure_file(${__reflect_open_cl_path__}/cl_reflect_config.hpp.in
                 ${__open_cl_config_path__}/cl_reflect_config.hpp)
  configure_file(${__reflect_open_cl_path__}/reflect_config.h.in
                 ${__open_cl_file_path__}/reflect_config.h)

  # ReflectOpenCl
  AddOpenClFiles("")
  AddOpenClFiles(Camera)
  AddOpenClFiles(Color)
  AddOpenClFiles(Data)
  AddOpenClFiles(DataStructure)
  AddOpenClFiles(LinearAlgebra)
  AddOpenClFiles(Material)
  AddOpenClFiles(RenderingMethod)
  AddOpenClFiles(Sampling)
  AddOpenClFiles(Utility)
  add_library(ReflectOpenCl SHARED ${__open_cl_source_files__})
  target_link_libraries(ReflectOpenCL ${OpenCL_LIBRARY}
                                      ${qt5_libraries}
                                      ${zisc_library}
                                      ${reflect_core_library})

  # Set variables
  set(reflect_open_cl_include_dirs ${__reflect_open_cl_path__} 
                                   ${__open_cl_config_path__})
  set(reflect_open_cl_library ReflectOpenCl)
endmacro(SetReflectOpenCl)
