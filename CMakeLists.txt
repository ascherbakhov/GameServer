cmake_minimum_required(VERSION 3.10)
project(Network)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/spdlog)
add_subdirectory(third-party/googletest)

include_directories(include third-party/googletest/googletest/include third-party/spdlog/include)

add_executable(Network src/main.cpp src/UDPSocket.cpp include/UDPSocket.h
               src/SocketHelpers.cpp include/SocketHelpers.h src/SockAddr.cpp
        include/SockAddr.h src/BitStream.cpp include/BitStream.h include/utils/ByteSwap.h)

add_executable(Tests tests/main.cpp tests/BitStreamTests.cpp include/BitStream.h src/BitStream.cpp tests/ByteSwap.cpp
        include/utils/ByteSwap.h)

target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Network spdlog)