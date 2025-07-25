find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_DIR})

include_directories(SYSTEM "${CMAKE_CURRENT_BINARY_DIR}")
include_directories(SYSTEM ${GENERATED_DIR})

BISON_TARGET(
        Parser
        "${CMAKE_CURRENT_SOURCE_DIR}/frontend/parser.yy"
        "${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp"
        DEFINES_FILE "${GENERATED_DIR}/parser.tab.hpp"
)

FLEX_TARGET(
        Lexer
        "${CMAKE_CURRENT_SOURCE_DIR}/frontend/lexer.ll"
        "${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp"
)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set(COMPILER_SOURCES
        main.cpp
        ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS})

add_executable(compiler ${COMPILER_SOURCES})
