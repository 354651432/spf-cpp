cmake_minimum_required(VERSION 3.0)
project(spf LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g)

add_executable(main main.cpp)