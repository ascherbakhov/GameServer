//
// Created by qazzer on 01.05.2019.
//


#include <TransferUtils/EntitiesRegistry.h>
#include "TransferUtils/ReplicationController.h"

void ReplicationController::AddEntitiesToStream(OutputBitStream &outputBitStream,
                                                const std::vector<Entity *> &replicatedEntities)
{
    outputBitStream.Write(PT_ReplicationData);
    outputBitStream.Write(replicatedEntities.size(), 16); //TODO: check
    for (auto entity : replicatedEntities)
    {
        AddEntityToStream(outputBitStream, entity);
    }
}

void ReplicationController::AddEntityToStream(OutputBitStream &outputBitStream, Entity *entity)
{
    outputBitStream.Write(mEntities->getID(entity, false));
    outputBitStream.Write(entity->GetEntityType());
    entity->Write(outputBitStream);
}

void ReplicationController::ReceiveEntitiesFromStream(InputBitStream &inputBitStream, uint32_t entitiesCount)
{
    std::unordered_set<Entity*> receivedEntities;
    while (entitiesCount > 0)
    {
        Entity* entity = ReceiveEntityFromStream(inputBitStream);
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

Entity * ReplicationController::ReceiveEntityFromStream(InputBitStream &inputBitStream)
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

void ReplicationController::CreateEntity(OutputBitStream &outputBitStream, Entity *entity)
{
    ReplicationHeader header(RA_Create, mEntities->getID(entity, true), entity->GetEntityType());
    outputBitStream.Write(header);
    entity->Write(outputBitStream);
}

void ReplicationController::UpdateEntity(OutputBitStream &outputBitStream, Entity *entity)
{
    ReplicationHeader header(RA_Update, mEntities->getID(entity, false), entity->GetEntityType());
    header.Write(outputBitStream);
    entity->Write(outputBitStream);
}

void ReplicationController::DeleteEntity(OutputBitStream &outputBitStream, Entity *entity)
{
    ReplicationHeader header(RA_Delete, mEntities->getID(entity, false), entity->GetEntityType());
    header.Write(outputBitStream);
}
