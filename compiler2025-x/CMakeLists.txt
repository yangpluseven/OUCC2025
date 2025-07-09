cmake_minimum_required(VERSION 3.21)
set(CMAKE_BUILD_TYPE Debug)
project(CarrotCompiler  VERSION 0.1
                        DESCRIPTION "Simple compiler targeted RV64 for SysY Language"
                        LANGUAGES CXX)
# Common build options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
option(BUILD_IR_TESTING "Build IR testing" OFF)
# set(BUILD_IR_TESTING true)

# Generic includes
set(INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/include")
include_directories(${INCLUDE_DIRECTORIES})

# Compiler sources
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_subdirectory(src)

add_subdirectory(runtime)

# # Unit tests
# option(BUILD_TESTING OFF)
# if(BUILD_TESTING)
#     add_subdirectory(test)
# endif(BUILD_TESTING)