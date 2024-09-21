cmake_minimum_required(VERSION 3.0.0)

set(__reflect_core_path__ ${CMAKE_CURRENT_LIST_DIR})

macro(AddCoreFiles dir_name)
  file(GLOB __core_cpp_files__ ${__reflect_core_path__}/${dir_name}/*.cpp)
  file(GLOB __core_hpp_files__ ${__reflect_core_path__}/${dir_name}/*.hpp)
  if(NOT "${dir_name}" STREQUAL "")
    string(REPLACE "/" "\\\\" __group_name__ "\\\\${dir_name}")
  endif()
  source_group(ReflectCore${__group_name__} FILES ${__core_cpp_files__} 
                                                  ${__core_hpp_files__})
  set(__core_source_files__ ${__core_source_files__} 
                            ${__core_cpp_files__} 
                            ${__core_hpp_files__})

  # For debug
  #  message("## Core name: ${dir_name}")
  #  message("## Group name: ${__group_name__}")
endmacro(AddCoreFiles)

# Defined variables
#   reflect_core_include_dirs:
#   reflect_core_library
macro(SetReflectCore)
  set(__core_config_path__ ${PROJECT_BINARY_DIR}/include/reflect_core)
  source_group(ReflectCore FILES ${__core_config_path__}/reflect_config.hpp)
  set(__core_source_files__ ${__core_source_files__} 
                            ${__core_config_path__}/reflect_config.hpp)

  # Set sampler type 
  if(REFLECT_SAMPLER STREQUAL "XSadd")
    set(sampler_type "zisc::XsaddEngin")
    set(sampler_header_path "zisc/xsadd_engin.hpp")
  elseif(REFLECT_SAMPLER STREQUAL "dSFMT")
    set(sampler_type "zisc::Dsfmt19937")
    set(sampler_header_path "zisc/dsfmt_engin.hpp")
  elseif(REFLECT_SAMPLER STREQUAL "Xorshift")
    set(sampler_type "zisc::XorshiftEngin")
    set(sampler_header_path "zisc/xorshift_engin.hpp")
  else()
    message(FATAL_ERROR "## \"${REFLECT_SAMPLER}\" is not supported.")
  endif()
  message(STATUS "## Sampler type: ${REFLECT_SAMPLER}")

  # BVH node
  set(max_node_objects 4)

  # Generate a config file
  configure_file(${__reflect_core_path__}/reflect_config.hpp.in
                 ${__core_config_path__}/reflect_config.hpp)

  # ReflectCore
  AddCoreFiles("")
  AddCoreFiles(CameraModel)
  AddCoreFiles(Color)
  AddCoreFiles(Data)
  AddCoreFiles(DataStructure)
  AddCoreFiles(Geometry)
  AddCoreFiles(LinearAlgebra)
  AddCoreFiles(Material)
  AddCoreFiles(Material/Bxdf)
  AddCoreFiles(Material/EmitterModel)
  AddCoreFiles(Material/Light)
  AddCoreFiles(Material/Sensor)
  AddCoreFiles(Material/SurfaceModel)
  AddCoreFiles(Material/Texture)
  AddCoreFiles(RendererBase)
  AddCoreFiles(RenderingMethod)
  AddCoreFiles(Sampling)
  AddCoreFiles(Tonemapping)
  AddCoreFiles(Utility)
  add_library(ReflectCore SHARED ${__core_source_files__})
  target_link_libraries(ReflectCore ${qt5_libraries} ${zisc_library})
  set_target_properties(ReflectCore PROPERTIES AUTOMOC ON)

  # Set variables
  set(reflect_core_include_dirs ${__reflect_core_path__} ${__core_config_path__})
  set(reflect_core_library ReflectCore)
endmacro(SetReflectCore)
