cmake_minimum_required(VERSION 3.21)
# 开启调试符号
set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(utils)
add_subdirectory(parser)
add_subdirectory(ir)
add_subdirectory(opt)
add_subdirectory(riscv)

set(SOURCE_FILES main.cpp)

add_executable(carrotcompiler ${SOURCE_FILES})
set_target_properties(carrotcompiler PROPERTIES OUTPUT_NAME "compiler")

target_include_directories(carrotcompiler PRIVATE utils parser ir opt riscv)

target_link_libraries(carrotcompiler utils parser ir opt riscv)

set_target_properties(carrotcompiler PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)