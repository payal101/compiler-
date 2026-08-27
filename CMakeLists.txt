cmake_minimum_required(VERSION 3.16)

project(ToyCompiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Found MLIR ${MLIR_VERSION}")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
    ${MLIR_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${MLIR_DEFINITIONS})


add_executable(toy

    main.cpp


    src/codegen/CodeGenerator.cpp

    
    src/lexer/Lexer.cpp

 
    src/parser/Parser.cpp

    
    src/ast/NumberExpr.cpp
    src/ast/BinaryExpr.cpp
    src/ast/VariableExpr.cpp
    src/ast/AssignmentExpr.cpp
    src/ast/ComparisionExpr.cpp
    src/ast/BlockStmt.cpp
    src/ast/Ifstmt.cpp
    src/ast/WhileStmt.cpp
    src/ast/BreakStmt.cpp
    src/ast/ContinueStmt.cpp
    src/ast/ForStmt.cpp
    src/ast/ReturnStmt.cpp
    src/ast/FunctionDec1.cpp
    src/ast/CallExpr.cpp

   
    src/semantic/SemanticAnalyzer.cpp
    src/semantic/Symbol.cpp
    src/semantic/SymbolTable.cpp
    src/semantic/Scope.cpp
    src/analysis/CFG.cpp
)


target_compile_options(toy PRIVATE
    -g
    -fsanitize=address
)

target_link_options(toy PRIVATE
    -fsanitize=address
)



target_link_libraries(toy PRIVATE
    /usr/lib/llvm-18/lib/libMLIR.so
    /usr/lib/llvm-18/lib/libLLVM.so
)



add_executable(SymbolTableTest

    tests/SymbolTableTest.cpp

    src/semantic/Symbol.cpp
    src/semantic/SymbolTable.cpp
)

target_compile_options(SymbolTableTest PRIVATE
    -g
    -fsanitize=address
)

target_link_options(SymbolTableTest PRIVATE
    -fsanitize=address
)