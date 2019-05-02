//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_REPLICATIONCONTROLLER_H
#define NETWORK_REPLICATIONCONTROLLER_H

#include <vector>
#include <unordered_set>
#include <DataStructures/OutputBitStream.h>
#include <Entity.h>
#include <TransferUtils/ReplicationUtils.h>
#include <Entities.h>

class ReplicationController {
public:
    explicit ReplicationController(Entities* entities): mEntities(entities) {};
    void AddEntitiesToStream(OutputBitStream &outputBitStream, const std::vector<Entity *> &replicatedEntities);
    void AddEntityToStream(OutputBitStream &outputBitStream, Entity *entity);
    void ReceiveEntitiesFromStream(InputBitStream &inputBitStream, uint32_t entitiesCount);
    Entity * ReceiveEntityFromStream(InputBitStream &inputBitStream);

    void CreateEntity(OutputBitStream& outputBitStream, Entity* entity);
    void UpdateEntity(OutputBitStream& outputBitStream, Entity* entity);
    void DeleteEntity(OutputBitStream& outputBitStream, Entity* entity);
private:
    Entities* mEntities;
    std::unordered_set<Entity*> mReplicatedEntities;
};


#endif //NETWORK_REPLICATIONCONTROLLER_H
