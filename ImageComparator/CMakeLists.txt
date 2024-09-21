cmake_minimum_required(VERSION 3.0.0)


## The project information
project(ImageComparator CXX)


set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 11)

file(GLOB source_files
		${PROJECT_SOURCE_DIR}/source/*.cpp)

include_directories(/Users/takemura/Programs/TristimulusValuesRenderer/ImageComparator)

## Load libraries
# libpng
find_package(PNG REQUIRED)
# include_directories(${PNG_INCLUDE_DIRS})
set(libraries ${libraries} ${PNG_LIBRARIES})
add_definitions(${PNG_DEFINITIONS})
# Boost 
find_package(Boost 1.50 REQUIRED COMPONENTS filesystem system thread)
include_directories(${Boost_INCLUDE_DIRS})
set(libraries ${libraries} ${Boost_LIBRARIES})



## Make execution file
add_executable(${PROJECT_NAME} ${source_files})
##add_executable(${PROJECT_NAME} ${source_files} ${header_files})
target_link_libraries(${PROJECT_NAME} ${libraries})
