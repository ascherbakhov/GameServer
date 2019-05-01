//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_ENTITYDESCRIPTIONMAP_H
#define NETWORK_ENTITYDESCRIPTIONMAP_H

#include <cstdint>
#include <unordered_map>
#include <Entities/Enemy.h>
#include <Entities/Vehicle.h>
#include <assert.h>
#include <functional>

class EntityDescriptionMap {
public:
    static EntityDescriptionMap& Get()
    {
        static EntityDescriptionMap sInstance;
        return sInstance;
    }

    template <class T>
    void RegisterEntity()
    {
        assert(mNameToEntityFunc.find(T::entityType) == mNameToEntityFunc.end());
        mNameToEntityFunc[T::entityType] = T::Create;
    }

    Entity* CreateEntityByType(uint32_t entityType)
    {
        auto entityCreatorFunc = mNameToEntityFunc[entityType];
        Entity* entity = entityCreatorFunc();
        return entity;
    }
private:
    std::unordered_map<uint32_t, std::function<Entity*()>> mNameToEntityFunc;
};

void RegisterEntity()
{
    EntityDescriptionMap::Get().RegisterEntity<Entity>();
    EntityDescriptionMap::Get().RegisterEntity<Vehicle>();
    EntityDescriptionMap::Get().RegisterEntity<Enemy>();
}

#endif //NETWORK_ENTITYDESCRIPTIONMAP_H
