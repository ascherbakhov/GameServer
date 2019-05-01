//
// Created by qazer on 11.04.2019.
//

#ifndef NETWORK_ENTITY_H
#define NETWORK_ENTITY_H


#include <cstdint>
#include <DataStructures/OutputBitStream.h>

class Entity
{
public:
    enum {entityType = 0};
    virtual uint32_t GetEntityType() const { return entityType;}
    static Entity* Create() { return new Entity();}
    virtual void Write(OutputBitStream& outputBitStream) const {};
};


#endif //NETWORK_ENTITY_H
