#include "EntitySystem.h"
#include <EntitySystem/Entity/Entity.h>

namespace ME
{
    void EntitySystem::Initialize()
    {

    }

    void EntitySystem::Update()
    {

    }

    Entity& EntitySystem::CreateEntity(const String& name)
    {
        mEntities.push_back(new Entity(this, name));
        return *mEntities.back();
    }
}