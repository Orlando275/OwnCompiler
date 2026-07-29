# Lox — My First Language (C++ port)

An interpreter for the **Lox** language implemented in **C++**, following the book
[*Crafting Interpreters*](https://craftinginterpreters.com/) by Robert Nystrom.

The book builds the `jlox` interpreter in **Java**; this project is a
**translation to modern C++ (C++20)**, done as a learning exercise — both to
understand how an interpreter works internally and to practice C++ itself.

## What is this?

Lox is a dynamic scripting language with functions, closures, classes and
inheritance. This project reimplements its tree-walking interpreter from
scratch, rewriting in C++ each stage the book presents in Java:

- **Scanner / Lexer** — turns the source code into tokens.
- **Parser** — builds the Abstract Syntax Tree (AST) from the tokens.
- **AST Printer** — walks the tree and prints it (handy for debugging the parser).
- **Interpreter** — evaluates the tree and runs the program *(in progress)*.

It can be used in two ways, just like in the book:

- **REPL** — interactive mode, running `lox` with no arguments.
- **File** — running a script with `lox script.lox`.

## Project structure

```
include/    Headers (Scanner, Parser, Expr, Token, TokenType, AstPrinter, Lox)
src/        Implementations (.cpp)
tests/      Tests (AstPrinterTest)
tools/      Utilities
CMakeLists.txt
```

## Build and run

Requires **CMake ≥ 3.16** and a compiler with **C++20** support.

```bash
cmake -S . -B build
cmake --build build

# Interactive REPL
./build/lox

# Run a file
./build/lox script.lox

# Run the tests
./build/test_astprinter
```

## Status

🚧 Work in progress. The scanner, parser and AST printer are currently
implemented; the interpreter and the following stages of the book will be
added next.

## Reference

- Book: [*Crafting Interpreters*](https://craftinginterpreters.com/) — Robert Nystrom
