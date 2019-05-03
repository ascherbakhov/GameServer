//
// Created by qazzer on 01.05.2019.
//


#include <Replication/EntitiesRegistry.h>
#include "Replication/ReplicationController.h"

void ReplicationController::ReplicateWorldState(OutputBitStream &outputBitStream,
                                                const std::vector<Entity *> &replicatedEntities)
{
    outputBitStream.Write(PT_ReplicationData);
    outputBitStream.Write(replicatedEntities.size());
    for (auto entity : replicatedEntities)
    {
        ReplicateEntity(outputBitStream, entity);
    }
}

void ReplicationController::ReplicateEntity(OutputBitStream &outputBitStream, Entity *entity)
{
    outputBitStream.Write(mEntities->getID(entity, false));
    outputBitStream.Write(entity->GetEntityType());
    entity->Write(outputBitStream);
}

void ReplicationController::ReceiveWorldState(InputBitStream &inputBitStream, uint32_t entitiesCount)
{
    std::unordered_set<Entity*> receivedEntities;
    while (entitiesCount > 0)
    {
        Entity* entity = ReceiveEntity(inputBitStream);
        receivedEntities.insert(entity);
        --entitiesCount;
    }

    for (auto entity : mReplicatedEntities)
    {
        if (receivedEntities.find(entity) != receivedEntities.end())
        {
            mEntities->RemoveEntity(entity);
            entity->Destroy();
        }
    }
}

Entity * ReplicationController::ReceiveEntity(InputBitStream &inputBitStream)
{
    uint32_t entityType;
    uint32_t entityID;
    inputBitStream.Read(entityID);
    inputBitStream.Read(entityType);
    Entity* entity = mEntities->get(entityID);
    if (!entity)
    {
        entity = EntitiesRegistry::Get().CreateEntityByType(entityType);
        mEntities->AddEntity(entity, entityID);
    }
    entity->Read(inputBitStream);
    return entity;
}

void ReplicationController::ReplicateCreate(OutputBitStream &outputBitStream, Entity *entity)
{
    ReplicationHeader header(RA_Create, mEntities->getID(entity, true), entity->GetEntityType());
    outputBitStream.Write(header);
    entity->Write(outputBitStream);
}

void ReplicationController::ReplicateUpdate(OutputBitStream &outputBitStream, Entity *entity)
{
    ReplicationHeader header(RA_Update, mEntities->getID(entity, false), entity->GetEntityType());
    header.Write(outputBitStream);
    entity->Write(outputBitStream);
}

void ReplicationController::ReplicateDelete(OutputBitStream &outputBitStream, Entity *entity)
{
    ReplicationHeader header(RA_Delete, mEntities->getID(entity, false), entity->GetEntityType());
    header.Write(outputBitStream);
}

void ReplicationController::ReceiveCreate(InputBitStream &inputBitStream, ReplicationHeader header)
{
    Entity* entity = EntitiesRegistry::Get().CreateEntityByType(header.entityType);
    mEntities->AddEntity(entity, header.entityID);
    entity->Read(inputBitStream);
}

void ReplicationController::ReceiveUpdate(InputBitStream &inputBitStream, ReplicationHeader header)
{
    Entity* entity = mEntities->get(header.entityID);
    if (entity)
    {
        entity->Read(inputBitStream);
    }
    else
    {
        entity = EntitiesRegistry::Get().CreateEntityByType(header.entityType);
        entity->Read(inputBitStream);
        delete entity;
    }
}

void ReplicationController::ReceiveDelete(InputBitStream &inputBitStream, ReplicationHeader header)
{
    Entity* entity = mEntities->get(header.entityID);
    mEntities->RemoveEntity(entity);
    entity->Destroy();
}

void ReplicationController::ProcessAction(InputBitStream &inputBitStream)
{
    ReplicationHeader header{};
    header.Read(inputBitStream);

    switch (header.action)
    {
        case RA_Create:
            ReceiveCreate(inputBitStream, header);
            break;
        case RA_Update:
            ReceiveUpdate(inputBitStream, header);
            break;
        case RA_Delete:
            ReceiveDelete(inputBitStream, header);
            break;
        default:
            break;
    }
}
