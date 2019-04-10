cmake_minimum_required(VERSION 3.10)
project(Network)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/spdlog)
add_subdirectory(third-party/googletest)

include_directories(include third-party/googletest/googletest/include third-party/spdlog/include)

add_executable(Network src/main.cpp src/UDPSocket.cpp include/UDPSocket.h
               src/SocketHelpers.cpp include/SocketHelpers.h src/SockAddr.cpp
        include/SockAddr.h include/utils/ByteSwap.h src/DataStructures/InputBitStream.cpp include/DataStructures/InputBitStream.h include/utils/Constants.h src/DataStructures/OutputBitStream.cpp include/DataStructures/OutputBitStream.h src/Entities.cpp include/Entities.h src/Entity.cpp include/Entity.h)

add_executable(Tests tests/main.cpp tests/BitStreamTests.cpp tests/ByteSwap.cpp
        include/utils/ByteSwap.h include/DataStructures/InputBitStream.h include/DataStructures/OutputBitStream.h
        src/DataStructures/InputBitStream.cpp src/DataStructures/OutputBitStream.cpp)

target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Network spdlog)