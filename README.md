# Toy Compiler in C++

A compiler written in C++ as a hands-on exploration of compiler design and LLVM.

The project implements the front-end of a small programming language and
generates LLVM IR as its intermediate representation. I am currently working
through SSA-based representations and optimizations.

## Pipeline

```text
Source Program
      │
      ▼
   Lexer
      │
      ▼
   Tokens
      │
      ▼
   Parser
      │
      ▼
    AST
      │
      ▼
 Code Generation
      │
      ▼
  LLVM IR
      │
      ▼
SSA / Optimizations
