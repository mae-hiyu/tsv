cmake_minimum_required(VERSION 3.0)

## Set command options
macro(SetCommandOptions)
  option(REFLECT_FLOAT_CHECK "Check if float data is valid" OFF)

  option(REFLECT_BUILD_EXTRA_TOOLS "Build extra tools" ON)

  option(REFLECT_BUILD_DOCUMENT "Build document using Doxygen" OFF)

  # Select random generator from "XSadd", "dSFMT", "Xorshift"
  set(REFLECT_SAMPLER "XSadd" CACHE STRING "")

  # Set memory pool size
  math(EXPR __default_memory_size__ "1 << 15")
  set(REFLECT_MEMORY_POOL_SIZE ${__default_memory_size__} CACHE STRING "")

  # The shortest wavelength of the spectra range
  set(REFLECT_SHORTEST_WAVELENGTH 380 CACHE STRING "")

  # The longest wavelength of the spectra range
  set(REFLECT_LONGEST_WAVELENGTH 780 CACHE STRING "")

  # The resolution of wavelength
  # 1 : High memory consumption, high accurate
  # 5
  # 10: Low memory consumption, low accurate
  set(REFLECT_WAVELENGTH_RESOLUTION 1 CACHE STRING "")

  # Wavelength sample size
  set(REFLECT_WAVELENGTH_SAMPLE_SIZE 12 CACHE STRING "")


  # Validate options
  set(__w_min__ ${REFLECT_SHORTEST_WAVELENGTH})
  set(__w_max__ ${REFLECT_LONGEST_WAVELENGTH})

  if(${__w_min__} LESS 300)
    message(FATAL_ERROR 
            "## The shortest wavelength must be greater than equal to 300nm.")
  endif()
  if(830 LESS ${__w_max__})
    message(FATAL_ERROR  
            "## The longest wavelength must be less than equal to 830nm.")
  endif()
  if(NOT (${__w_min__} LESS ${__w_max__}))
    message(FATAL_ERROR 
            "## The shortest wavelength must be less than to the longest.")
  endif()

  set(__delta_w__ ${REFLECT_WAVELENGTH_RESOLUTION})
  if(NOT 0 LESS ${__delta_w__})
    message(FATAL_ERROR "## Wavelength resolution is must be natural number.")
  endif()
  math(EXPR __w_range__ "${__w_max__} - ${__w_min__}")
  math(EXPR __r__ "${__w_range__} % ${__delta_w__}")
  if(NOT ${__r__} EQUAL 0)
    message(FATAL_ERROR "## Invalied wavelength resolution is specified.")
  endif()

  math(EXPR __spectra_size__ "${__w_range__} / ${__delta_w__}")
  set(__w_samples__ ${REFLECT_WAVELENGTH_SAMPLE_SIZE})
  # !(0 < sampleSize <= spectraSize)
  if(NOT (0 LESS ${__w_samples__} AND 
          (${__w_samples__} LESS ${__spectra_size__} OR
           ${__w_samples__} EQUAL ${__spectra_size__})))
    message(FATAL_ERROR "## Invalid wavelength sample size is specified.")
  endif()
endmacro(SetCommandOptions)
