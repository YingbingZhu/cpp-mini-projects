cmake_minimum_required(VERSION 3.30)
project(encryptor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

include_directories(${SODIUM_INCLUDE_DIRS})
link_directories(${SODIUM_LIBRARY_DIRS})

add_executable(encryptor main.cpp encryptor.cpp)
target_link_libraries(encryptor ${SODIUM_LIBRARIES})

add_executable(test_encryptor test_encryptor.cpp encryptor.cpp)
target_link_libraries(test_encryptor ${SODIUM_LIBRARIES})

target_compile_features(encryptor PRIVATE cxx_std_17)
