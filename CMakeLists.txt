cmake_minimum_required(VERSION 3.10)
project(Network)

add_subdirectory(third-party/spdlog)

set(CMAKE_CXX_STANDARD 14)

add_executable(Network main.cpp UDPSocket.cpp UDPSocket.h SocketHelpers.cpp SocketHelpers.h NetworkInterface.cpp NetworkInterface.h IStream.cpp IStream.h)

target_link_libraries(Network spdlog)