cmake_minimum_required(VERSION 3.10)
project(Network)

add_subdirectory(third-party/spdlog)

set(CMAKE_CXX_STANDARD 14)

add_executable(Network main.cpp UDPSocket.cpp UDPSocket.h SocketUtils.cpp SocketUtils.h SocketAddress.cpp SocketAddress.h)

target_link_libraries(Network spdlog)