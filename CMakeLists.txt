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
    src/ast/ComparisionExpr.cpp
    src/semantic/SemanticAnalyzer.cpp
    src/ast/BlockStmt.cpp

  src/ast/Ifstmt.cpp
  src/ast/WhileStmt.cpp
  src/ast/BreakStmt.cpp
src/ast/ContinueStmt.cpp
src/ast/ForStmt.cpp
src/ast/ReturnStmt.cpp
src/ast/FunctionDec1.cpp
src/ast/CallExpr.cpp
)
add_executable(SymbolTableTest
    tests/SymbolTableTest.cpp
    src/semantic/Symbol.cpp
    src/semantic/SymbolTable.cpp
)
target_compile_options(toy PRIVATE -fsanitize=address -g)
target_link_options(toy PRIVATE -fsanitize=address)
llvm_map_components_to_libnames(
    LLVM_LIBS
    core
    support
)
target_compile_options(SymbolTableTest PRIVATE -fsanitize=address -g)
target_link_options(SymbolTableTest PRIVATE -fsanitize=address)