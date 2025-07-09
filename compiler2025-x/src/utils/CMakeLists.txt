set(SOURCE_FILES utils.cpp)

add_library(utils STATIC ${SOURCE_FILES})

# target_include_directories(utils PRIVATE ${CMAKE_SOURCE_DIR}/src/ir)