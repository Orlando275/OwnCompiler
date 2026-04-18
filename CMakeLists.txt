cmake_minimum_required(VERSION 3.16)
project(LoxMyFirstLanguage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lox
    src/Scanner.cpp
    src/Lox.cpp
    src/AstPrinter.cpp
)
target_include_directories(lox PRIVATE include)

add_executable(test_astprinter
    src/AstPrinter.cpp
    tests/AstPrinterTest.cpp
)
target_include_directories(test_astprinter PRIVATE include)