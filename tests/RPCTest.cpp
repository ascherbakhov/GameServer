//
// Created by qazzer on 04.05.2019.
//
#include <gtest/gtest.h>
#include <Replication/RPCController.h>
#include <spdlog/spdlog.h>
#include <Replication/ReplicationUtils.h>

void MakeRPCCallTest(OutputBitStream& outputBitStream, uint32_t name, uint32_t Arg1, std::string Arg2)
{
    ReplicationHeader header(RA_RPC);
    header.Write(outputBitStream);

    outputBitStream.Write(name);
    outputBitStream.Write(Arg1);
    outputBitStream.Write(Arg2);
}

void TestRPCFunction(InputBitStream& inputBitStream)
{
    uint32_t Arg1;
    std::string Arg2;
    inputBitStream.Read(Arg1);
    inputBitStream.Read(Arg2);
    spdlog::debug("TestArg1:{}, TestArg2:{}", Arg1, Arg2);
}

TEST(RPCTests, Test1)
{
    auto entities = new Entities();
    auto rpcController = new RPCController(entities);
    rpcController->RegisterRPCFunction(1, TestRPCFunction);

    OutputBitStream outputBitStream(256);
    MakeRPCCallTest(outputBitStream, 1, 345, std::string("Hello"));

    InputBitStream inputBitStream(outputBitStream.GetBuffer(), outputBitStream.GetSize());
    ReplicationHeader header{};
    header.Read(inputBitStream);
    rpcController->ReceiveRPC(inputBitStream);

}
