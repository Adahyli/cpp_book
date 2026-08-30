cmake_minimum_required(VERSION 3.20)

project(calculator LANGUAGES CXX)

add_executable(calculator
    src/main.cpp
    src/Calculator.cpp
    src/TokenStream.cpp
    src/SymbolTable.cpp
)

target_include_directories(calculator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(calculator PRIVATE cxx_std_20)