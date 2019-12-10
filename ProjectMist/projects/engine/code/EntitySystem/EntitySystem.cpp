#include "MistEngine_PCH.h"

#include "EntitySystem.h"
#include <EntitySystem/Entity/Entity.h>

namespace ME
{
    void EntitySystem::OnInitialize()
    {
        for (auto& en : mEntities)
            en->OnEntityInitialize();
    }

    void EntitySystem::OnUpdate()
    {
        for (auto& en : mEntities)
            en->OnEntityUpdate();
    }

    Entity& EntitySystem::CreateEntity(const String& name)
    {
        mEntities.push_back(new Entity(&GetEngine(), name));
        return *mEntities.back();
    }
}