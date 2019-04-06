cmake_minimum_required(VERSION 3.10)
project(Network)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/spdlog)
add_subdirectory(third-party/googletest)

include_directories(src/include third-party/googletest/googletest/include)

add_executable(Network src/main.cpp src/UDPSocket.cpp src/include/UDPSocket.h
               src/SocketHelpers.cpp src/include/SocketHelpers.h src/SockAddr.cpp
        src/include/SockAddr.h src/BitStream.cpp src/include/BitStream.h)

add_executable(Tests tests/main.cpp tests/BitStreamTests.cpp)

target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Network spdlog)