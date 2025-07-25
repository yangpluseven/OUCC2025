cmake_minimum_required(VERSION 3.31)
project(OUCC2025)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "${PROJECT_SOURCE_DIR}")

include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)
