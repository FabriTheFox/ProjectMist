#include "EntitySystem.h"
#include <EntitySystem/Entity/Entity.h>

namespace ME
{
    void EntitySystem::OnInitialize()
    {

    }

    void EntitySystem::OnUpdate()
    {

    }

    Entity& EntitySystem::CreateEntity(const String& name)
    {
        mEntities.push_back(new Entity(this, name));
        return *mEntities.back();
    }
}