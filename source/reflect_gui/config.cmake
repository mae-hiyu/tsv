cmake_minimum_required(VERSION 3.0.0)

set(__reflect_gui_path__ ${CMAKE_CURRENT_LIST_DIR})

macro(AddGuiFiles dir_name)
  file(GLOB __gui_cpp_files__ ${__reflect_gui_path__}/${dir_name}/*.cpp)
  file(GLOB __gui_hpp_files__ ${__reflect_gui_path__}/${dir_name}/*.hpp)
  if(NOT "${dir_name}" STREQUAL "")
    string(REPLACE "/" "\\\\" __group_name__ "\\\\${dir_name}")
  endif()
  source_group(ReflectGui${__group_name__} FILES ${__gui_cpp_files__} 
                                                 ${__gui_hpp_files__})
  set(__gui_source_files__ ${__gui_source_files__} 
                           ${__gui_cpp_files__} ${__gui_hpp_files__})

  # For debug
  #  message("## Gui name: ${dir_name}")
  #  message("## Group name: ${__group_name__}")
endmacro(AddGuiFiles)

# Defined variables
#   reflect_gui_include_dir:
#   reflect_gui_library
macro(SetReflectGui)
  # ReflectGui
  AddGuiFiles("")
  AddGuiFiles(BasicSettings)
  AddGuiFiles(BasicSettings/BvhWidget)
  AddGuiFiles(BasicSettings/RenderingMethodWidget)
  AddGuiFiles("Command")
  AddGuiFiles(MaterialWidget)
  AddGuiFiles(MaterialWidget/EmitterModelWidget)
  AddGuiFiles(MaterialWidget/SurfaceModelWidget)
  AddGuiFiles(MaterialWidget/TextureWidget)
  AddGuiFiles(ObjectWidget)
  AddGuiFiles(TransformationWidget)
  add_library(ReflectGui SHARED ${__gui_source_files__} ${reflect_ui_hpp_files})
  target_link_libraries(ReflectGui ${qt5_libraries} 
                                   ${zisc_library}
                                   ${reflect_core_library}
                                   ${reflect_renderer_library})
  set_target_properties(ReflectGui PROPERTIES AUTOMOC ON)

  # Set variables
  set(reflect_gui_include_dir ${__reflect_gui_path__})
  set(reflect_gui_library ReflectGui)
endmacro(SetReflectGui)
