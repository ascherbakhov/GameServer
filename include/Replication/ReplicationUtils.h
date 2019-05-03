//
// Created by qazzer on 27.04.2019.
//

#ifndef NETWORK_REPLICATIONUTILS_H
#define NETWORK_REPLICATIONUTILS_H

#include <DataStructures/InputBitStream.h>
#include <DataStructures/OutputBitStream.h>

enum PacketType
{
    PT_Hello,
    PT_ReplicationData,
    PT_Disconnect,
    PT_Max
};

enum ReplicationAction
{
    RA_Create,
    RA_Delete,
    RA_Update,
    RA_RPC,
    RA_RMI,
    RA_Max
};


class ReplicationHeader
{
public:
    ReplicationHeader() = default;
    ReplicationHeader(ReplicationAction action, uint32_t entityID, uint32_t entityType):
    action(action), entityID(entityID), entityType(entityType) {}
    void Write(OutputBitStream& outputBitStream);
    void Read(InputBitStream& inputBitStream);

    ReplicationAction action;
    uint32_t entityID;
    uint32_t entityType;
};

#endif //NETWORK_REPLICATIONUTILS_H
