cmake_minimum_required(VERSION 3.16)
project(compile2025-0)

# 默认使用 Debug 模式（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# 使用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用 AddressSanitizer（仅 Debug 模式）
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer -g")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置源文件
file(GLOB_RECURSE LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/lib/*.cpp
    ${CMAKE_SOURCE_DIR}/lib/ir/*.cpp
    ${CMAKE_SOURCE_DIR}/lib/parser/*.cpp
)

message(STATUS "LIB_SOURCES: ${LIB_SOURCES}")

# 创建可执行文件或库
add_executable(compiler2025-0 ${LIB_SOURCES})
