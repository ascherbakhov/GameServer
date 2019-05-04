//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_REPLICATIONCONTROLLER_H
#define NETWORK_REPLICATIONCONTROLLER_H

#include <vector>
#include <unordered_set>
#include <DataStructures/OutputBitStream.h>
#include <Entity.h>
#include <Replication/ReplicationUtils.h>
#include <Entities.h>

class ReplicationController
{
public:
    explicit ReplicationController(Entities* entities) : mEntities(entities)
    {};

    void ReplicateWorldState(OutputBitStream& outputBitStream, const std::vector<Entity*>& replicatedEntities);

    void ReplicateEntity(OutputBitStream& outputBitStream, Entity* entity);

    void ReceiveWorldState(InputBitStream& inputBitStream, uint32_t entitiesCount);

    Entity* ReceiveEntity(InputBitStream& inputBitStream);

    void ReplicateCreate(OutputBitStream& outputBitStream, Entity* entity);

    void ReplicateUpdate(OutputBitStream& outputBitStream, Entity* entity);

    void ReplicateDelete(OutputBitStream& outputBitStream, Entity* entity);

    void ReceiveCreate(InputBitStream& inputBitStream, ReplicationHeader header);

    void ReceiveUpdate(InputBitStream& inputBitStream, ReplicationHeader header);

    void ReceiveDelete(InputBitStream& inputBitStream, ReplicationHeader header);

    void ProcessAction(InputBitStream& inputBitStream);

private:
    Entities* mEntities;
    std::unordered_set<Entity*> mReplicatedEntities;
//    std::unordered_map<ReplicationAction , std::function<void()>> actionsMap{};
};


#endif //NETWORK_REPLICATIONCONTROLLER_H
