cmake_minimum_required(VERSION 3.10)
project(Network)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(third-party/spdlog)
add_subdirectory(third-party/googletest)

include_directories(include third-party/googletest/googletest/include third-party/spdlog/include)

add_executable(Network src/main.cpp src/SocketUtils/UDPSocket.cpp include/SocketUtils/UDPSocket.h
        src/SocketUtils/SocketHelpers.cpp include/SocketUtils/SocketHelpers.h src/SocketUtils/SockAddr.cpp
        include/SocketUtils/SockAddr.h include/utils/ByteSwap.h src/DataStructures/InputBitStream.cpp include/DataStructures/InputBitStream.h include/utils/Constants.h src/DataStructures/OutputBitStream.cpp include/DataStructures/OutputBitStream.h src/Entities.cpp include/Entities.h src/Entity.cpp include/Entity.h include/Replication/ReplicationUtils.h src/Entities/Vehicle.cpp include/Entities/Vehicle.h src/Entities/Enemy.cpp include/Entities/Enemy.h include/Replication/EntitiesRegistry.h src/Replication/ReplicationController.cpp include/Replication/ReplicationController.h src/Replication/ReplicationUtils.cpp src/Replication/RPCController.cpp include/Replication/RPCController.h)

add_executable(Tests tests/main.cpp tests/BitStreamTests.cpp tests/ByteSwap.cpp
        include/utils/ByteSwap.h include/DataStructures/InputBitStream.h include/DataStructures/OutputBitStream.h
        src/DataStructures/InputBitStream.cpp src/DataStructures/OutputBitStream.cpp
        src/Replication/RPCController.cpp include/Replication/RPCController.h
        src/Replication/ReplicationUtils.cpp include/Replication/ReplicationUtils.h tests/RPCTest.cpp)

target_link_libraries(Tests gtest gtest_main)
target_link_libraries(Network spdlog)