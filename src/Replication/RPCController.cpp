//
// Created by qazzer on 04.05.2019.
//

#include "Replication/RPCController.h"

void RPCController::RegisterRPCFunction(uint32_t functionID, RPCFunction function)
{
    assert (mRPCTable.find(functionID) == mRPCTable.end());
    mRPCTable[functionID] = std::move(function);
}

void RPCController::ReceiveRPC(InputBitStream& inputBitStream)
{
    uint32_t functionID;
    inputBitStream.Read(functionID);
    mRPCTable[functionID](inputBitStream);
}
