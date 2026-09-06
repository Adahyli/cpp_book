cmake_minimum_required(VERSION 3.20)

project(calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(calculator
    src/main.cpp
    src/Calculator.cpp
    src/SymbolTable.cpp
    src/TokenStream.cpp
)

target_include_directories(calculator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)