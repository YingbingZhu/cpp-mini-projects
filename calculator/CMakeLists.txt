cmake_minimum_required(VERSION 3.30)
project(calculator)

set(CMAKE_CXX_STANDARD 17)


add_executable(calculator calculator.cpp calculator.h)
target_compile_features(calculator PRIVATE cxx_std_17)