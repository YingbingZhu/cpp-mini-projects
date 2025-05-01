cmake_minimum_required(VERSION 3.30)
project(chat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Enable pthreads on Linux/macOS
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

# Build server executable
add_executable(chat_server server/chat_server.cpp)
target_link_libraries(chat_server PRIVATE ${OPENSSL_LIBRARIES} Threads::Threads)

# Build client executable
add_executable(chat_client client/chat_client.cpp)
target_link_libraries(chat_client PRIVATE ${OPENSSL_LIBRARIES} Threads::Threads)