//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_REPLICATIONCONTROLLER_H
#define NETWORK_REPLICATIONCONTROLLER_H

#include <vector>
#include <DataStructures/OutputBitStream.h>
#include <Entity.h>
#include <TransferUtils/ReplicationUtils.h>
#include <Entities.h>

class ReplicationController {
public:
    ReplicationController() = default;
    void ReplicateEntities(OutputBitStream &outputBitStream, const std::vector<Entity*>& replicatedEntities);
    void ReplicateEntity(OutputBitStream& outputBitStream, Entity* entity);
private:
    Entities* mEntities;
};


#endif //NETWORK_REPLICATIONCONTROLLER_H
