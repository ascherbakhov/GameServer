//
// Created by qazzer on 03.05.2019.
//
#include "Replication/ReplicationUtils.h"

void ReplicationHeader::Read(InputBitStream &inputBitStream)
{
    inputBitStream.Read(action);
    inputBitStream.Read(entityID);
    if (action != RA_Delete and action != RA_RPC)
    {
        inputBitStream.Read(entityType);
    }
}

void ReplicationHeader::Write(OutputBitStream &outputBitStream)
{
    outputBitStream.Write(action);
    outputBitStream.Write(entityID);
    if (action != RA_Delete and action != RA_RPC)
    {
        outputBitStream.Write(entityType);
    }
}
