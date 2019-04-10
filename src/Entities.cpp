//
// Created by qazer on 11.04.2019.
//

#include "Entities.h"

eid_t Entities::getID(Entity* entity)
{
    auto result = entitiesIDs.find(entity);
    return result == entitiesIDs.end() ? result->second : 0;
}

Entity* Entities::operator[](eid_t entityID)
{
    return get(entityID);
}

Entity* Entities::get(eid_t entityID)
{
    auto result = entities.find(entityID);
    return result == entities.end() ? result->second : nullptr;
}

void Entities::Write(Entity *entity)
{
    eid_t entityID = getID(entity);
    mOutpuBitStream->Write(entityID);
}


void Entities::Read(Entity *&entity)
{
    eid_t entityID;
    mInputBitStream->Read(entityID);
    entity = get(entityID);
}

