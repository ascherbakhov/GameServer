//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_ENEMY_H
#define NETWORK_ENEMY_H


#include <Entity.h>

class Enemy: public Entity {
public:
    explicit Enemy(uint16_t health): mHealth(health){}
    enum {entityType = 1};
    uint32_t GetEntityType() const override { return entityType;}
    static Entity* Create() { return new Enemy(100); }
    void Write(OutputBitStream& outputBitStream);
    void Read(InputBitStream &inputBitStream);
    void Destroy();
private:
    uint16_t mHealth;
};


#endif //NETWORK_ENEMY_H
