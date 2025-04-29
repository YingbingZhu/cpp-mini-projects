cmake_minimum_required(VERSION 3.20)
project(udp_echo)

# Set C++ standard globally
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if none specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_executable(udp_client udp_client.cpp)
add_executable(udp_server udp_server.cpp)