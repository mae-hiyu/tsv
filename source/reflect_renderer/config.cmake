cmake_minimum_required(VERSION 3.0.0)

set(__reflect_renderer_path__ ${CMAKE_CURRENT_LIST_DIR})

macro(AddRendererFiles dir_name)
  aux_source_directory(${__reflect_renderer_path__}/${dir_name}/ 
                       __renderer_cpp_files__)
  file(GLOB __renderer_hpp_files__ ${__reflect_renderer_path__}/${dir_name}/*.hpp)
  if(NOT "${dir_name}" STREQUAL "")
    string(REPLACE "/" "\\\\" __group_name__ "\\\\${dir_name}")
  endif()
  source_group(ReflectRenderer${__group_name__} FILES ${__renderer_cpp_files__} 
                                                      ${__renderer_hpp_files__})
  set(__renderer_source_files__ ${__renderer_source_files__} 
                                ${__renderer_cpp_files__} 
                                ${__renderer_hpp_files__})

  # For debug
  #  message("## Renderer name: ${dir_name}")
  #  message("## Group name: ${__group_name__}")
endmacro(AddRendererFiles)

# Defined variables
#   reflect_renderer_include_dir:
#   reflect_renderer_library
macro(SetReflectRenderer)
  # ReflectRenderer
  AddRendererFiles("")
  add_library(ReflectRenderer SHARED ${__renderer_source_files__})
  target_link_libraries(ReflectRenderer ${qt5_libraries} 
                                        ${zisc_library}
                                        ${reflect_core_library}
                                        ${reflect_open_cl_library})

  # Set variables
  set(reflect_renderer_include_dir ${__reflect_renderer_path__})
  set(reflect_renderer_library ReflectRenderer)
endmacro(SetReflectRenderer)
