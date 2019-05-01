//
// Created by qazzer on 01.05.2019.
//


#include "TransferUtils/ReplicationController.h"

void ReplicationController::ReplicateEntities(OutputBitStream &outputBitStream,
                                              const std::vector<Entity *> &replicatedEntities)
{
    outputBitStream.Write(PT_ReplicationData);
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
