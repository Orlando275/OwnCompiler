# Lox — Mi primer lenguaje (port a C++)

Intérprete del lenguaje **Lox** implementado en **C++**, siguiendo el libro
[*Crafting Interpreters*](https://craftinginterpreters.com/) de Robert Nystrom.

El libro construye el intérprete `jlox` en **Java**; este proyecto es una
**traducción a C++ moderno (C++20)** hecha como ejercicio de aprendizaje, tanto
del funcionamiento interno de un intérprete como del propio lenguaje C++.

## ¿Qué es esto?

Lox es un lenguaje de scripting dinámico con funciones, closures, clases y
herencia. Aquí se reimplementa desde cero su intérprete de árbol
(*tree-walking interpreter*), reescribiendo en C++ cada etapa que el libro
presenta en Java:

- **Scanner / Lexer** — convierte el código fuente en tokens.
- **Parser** — construye el Árbol de Sintaxis Abstracta (AST) a partir de los tokens.
- **AST Printer** — recorre el árbol y lo imprime (útil para depurar el parser).
- **Intérprete** — evalúa el árbol y ejecuta el programa *(en progreso)*.

Se puede usar de dos formas, igual que en el libro:

- **REPL** — modo interactivo, ejecutando `lox` sin argumentos.
- **Archivo** — ejecutando un script con `lox script.lox`.

## Estructura del proyecto

```
include/    Cabeceras (Scanner, Parser, Expr, Token, TokenType, AstPrinter, Lox)
src/        Implementaciones (.cpp)
tests/      Pruebas (AstPrinterTest)
tools/      Utilidades
CMakeLists.txt
```

## Compilar y ejecutar

Requiere **CMake ≥ 3.16** y un compilador con soporte de **C++20**.

```bash
cmake -S . -B build
cmake --build build

# REPL interactivo
./build/lox

# Ejecutar un archivo
./build/lox script.lox

# Correr las pruebas
./build/test_astprinter
```

## Estado

🚧 En desarrollo. Actualmente están implementados el scanner, el parser y el
AST printer; el intérprete y las siguientes etapas del libro se irán añadiendo.

## Referencia

- Libro: [*Crafting Interpreters*](https://craftinginterpreters.com/) — Robert Nystrom
