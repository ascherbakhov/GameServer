//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_ENEMY_H
#define NETWORK_ENEMY_H


#include <Entity.h>

class Enemy: public Entity {
public:
    enum {entityType = 1};
    uint32_t GetEntityType() const override { return entityType;}
    static Entity* Create() { return new Enemy(); }
};


#endif //NETWORK_ENEMY_H
