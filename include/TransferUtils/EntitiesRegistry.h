//
// Created by qazzer on 01.05.2019.
//

#ifndef NETWORK_ENTITIESREGISTRY_H
#define NETWORK_ENTITIESREGISTRY_H

#include <cstdint>
#include <unordered_map>
#include <Entities/Enemy.h>
#include <Entities/Vehicle.h>
#include <assert.h>
#include <functional>

class EntitiesRegistry {
public:
    static EntitiesRegistry& Get()
    {
        static EntitiesRegistry sInstance;
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
    EntitiesRegistry::Get().RegisterEntity<Entity>();
    EntitiesRegistry::Get().RegisterEntity<Vehicle>();
    EntitiesRegistry::Get().RegisterEntity<Enemy>();
}

#endif //NETWORK_ENTITIESREGISTRY_H
