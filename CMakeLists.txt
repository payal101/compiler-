cmake_minimum_required(VERSION 3.16)
project(ToyCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(
    include
    ${LLVM_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})

add_executable(toy
    main.cpp
    src/codegen/CodeGenerator.cpp
    src/ast/NumberExpr.cpp
    src/ast/BinaryExpr.cpp
    src/lexer/Lexer.cpp
    src/parser/Parser.cpp
    src/ast/VariableExpr.cpp
    src/ast/AssignmentExpr.cpp
)

llvm_map_components_to_libnames(
    LLVM_LIBS
    core
    support
)

target_link_libraries(toy ${LLVM_LIBS})