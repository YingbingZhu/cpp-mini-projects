cmake_minimum_required(VERSION 3.30)
project(spaceship)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(spaceship src/Main.cpp
        src/Player.cpp
        headers/Player.h
        headers/Bullet.h)
target_compile_features(spaceship PRIVATE cxx_std_17)

# Link SFML Graphics
target_link_libraries(spaceship PRIVATE SFML::Graphics)