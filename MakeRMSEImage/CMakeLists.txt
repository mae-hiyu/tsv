cmake_minimum_required(VERSION 3.0.0)


## The project information
project(RMSEIMaker CXX)

file(GLOB Main_sources
	${PROJECT_SOURCE_DIR}/source/*.cpp)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
MESSAGE(STATUS "flags --> CMAKE_CXX_FLAGS")
include_directories(/Users/takemura/Programs/TristimulusValuesRenderer/MakeRMSEImage)

## Load libraries
# libpng
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
set(libraries ${libraries} ${PNG_LIBRARIES})
add_definitions(${PNG_DEFINITIONS})
# Boost 
find_package(Boost 1.50 REQUIRED COMPONENTS filesystem system thread)
include_directories(${Boost_INCLUDE_DIRS})
set(libraries ${libraries} ${Boost_LIBRARIES})


## Make execution file
# add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/source/main.cpp
# 															 ${PROJECT_SOURCE_DIR}/source/filesystem.cpp
# 															 ${PROJECT_SOURCE_DIR}/source/manipulatePNG.cpp
# 															 ${PROJECT_SOURCE_DIR}/source/manipulateSPI.cpp
# 															 ${PROJECT_SOURCE_DIR}/source/WorkPile.cpp
# 															 ${PROJECT_SOURCE_DIR}/source/pseudo-color.cpp)
add_executable(${PROJECT_NAME} ${Main_sources})
##add_executable(${PROJECT_NAME} ${source_files} ${header_files})
target_link_libraries(${PROJECT_NAME} ${libraries})
