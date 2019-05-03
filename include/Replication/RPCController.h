//
// Created by qazzer on 04.05.2019.
//

#ifndef NETWORK_RPCCONTROLLER_H
#define NETWORK_RPCCONTROLLER_H


#include <unordered_map>
#include <functional>
#include <assert.h>

#include <DataStructures/InputBitStream.h>
#include <Entities.h>

typedef std::function<void(InputBitStream&)>* RPCFunction;

class RPCController {
public:
    explicit RPCController(Entities* entities)
    {
        mEntities = entities;
    }
    void RegisterRPCFunction(uint32_t functionID, RPCFunction function);
    void ReceiveRPC(InputBitStream& inputBitStream);
private:
    std::unordered_map<uint32_t, RPCFunction> mRPCTable;
    Entities* mEntities;
};


#endif //NETWORK_RPCCONTROLLER_H
