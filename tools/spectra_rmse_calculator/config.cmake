cmake_minimum_required(VERSION 3.0)

set(__spectra_rmse_calculator_path__ ${CMAKE_CURRENT_LIST_DIR})

macro(BuildSpectraRmseCalculator)
  set(__source_files__ ${__spectra_rmse_calculator_path__}/spectra_rmse_calculator.cpp)

  add_executable(SpectraRmseCalculator ${__source_files__})
  target_link_libraries(SpectraRmseCalculator ${zisc_library} ${Qt5Core_LIBRARIES})
endmacro(BuildSpectraRmseCalculator)
