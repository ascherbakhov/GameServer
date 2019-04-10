//
// Created by qazer on 11.04.2019.
//

#ifndef NETWORK_ENTITIES_H
#define NETWORK_ENTITIES_H

#include <cstdint>
#include <unordered_map>
#include <DataStructures/OutputBitStream.h>
#include <DataStructures/InputBitStream.h>
#include "Entity.h"

typedef uint32_t eid_t;

class Entities
{
public:
    eid_t getID(Entity* entity);

    Entity* operator[](eid_t entityID);
    Entity* get(eid_t);

    void Write(Entity* entity);
    void Read(Entity*& entity);

private:
    std::unordered_map<eid_t, Entity*> entities;
    std::unordered_map<Entity*, eid_t> entitiesIDs;

    OutputBitStream* mOutpuBitStream;
    InputBitStream* mInputBitStream;
};


#endif //NETWORK_ENTITIES_H
