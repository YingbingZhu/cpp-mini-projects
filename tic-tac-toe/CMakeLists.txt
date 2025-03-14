cmake_minimum_required(VERSION 3.30)
project(tic-tac-toe)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Copy the resource files to the build directory
configure_file(${CMAKE_SOURCE_DIR}/tic-tac-toe/font/Arial.ttf ${CMAKE_CURRENT_BINARY_DIR}/font/Arial.ttf COPYONLY)


# Add executable for tic-tac-toe
add_executable(tic-tac-toe src/main.cpp src/board.cpp)
target_compile_features(tic-tac-toe PRIVATE cxx_std_17)

# Link SFML Graphics
target_link_libraries(tic-tac-toe PRIVATE SFML::Graphics)

