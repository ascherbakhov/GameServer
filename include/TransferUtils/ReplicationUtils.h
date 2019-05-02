//
// Created by qazzer on 27.04.2019.
//

#ifndef NETWORK_REPLICATIONUTILS_H
#define NETWORK_REPLICATIONUTILS_H

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
    RA_Max
};


#endif //NETWORK_REPLICATIONUTILS_H
