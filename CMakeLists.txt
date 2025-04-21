cmake_minimum_required(VERSION 3.20)
project(cpp-mini-projects)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if none specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add subdirectories for each subproject
add_subdirectory(tic-tac-toe)
add_subdirectory(spaceship)
add_subdirectory(calculator)