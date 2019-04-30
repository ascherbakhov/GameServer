//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_VEHICLE_H
#define NETWORK_VEHICLE_H


#include <Entity.h>

class Vehicle: public Entity{
public:
    enum {entityType = 2};
    uint32_t GetEntityType() const override { return entityType; }
    static Entity* Create() { return new Vehicle();}
};


#endif //NETWORK_VEHICLE_H
