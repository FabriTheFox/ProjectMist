#include "MistEngine_PCH.h"

#include "Entity.h"
#include <EntitySystem/Component/Component.h>
#include <EntitySystem/EntitySystem.h>
#include <Engine/MistEngine.h>

namespace ME
{
    RTTI_IMPLEMENTATION(Entity);

    Entity::Entity(MistEngine* engine /*= nullptr*/, const String& name /*= ""*/)
        : mEngine(engine)
        , mName(name)
    {
    }

    Entity::~Entity()
    {
        for (auto& comp : mComponents)
            comp.second->MarkForDeletion();
    }

    void Entity::OnEntityInitialize()
    {
        OnInitialize();

        for (auto& comp : mComponents)
            comp.second->OnInitialize();
    }

    void Entity::OnEntityUpdate()
    {
        OnUpdate();

        for (auto& comp : mComponents)
            comp.second->OnUpdate();
    }

    void Entity::OnEntityPredestroy()
    {
        OnPredestroy();

        for (auto& comp : mComponents)
            comp.second->OnPredestroy();
    }

    Component& Entity::AddComponent(const RTTI& type)
    {
        auto& comp = mComponents[type];
        
        if (comp)
        {
            _ASSERT_EXPR(false, "Component already exists");
        }
        
        comp = type.CreateRawAs<Component>();
        comp->mOwner = this;

        comp->OnRegister(*mEngine);

        return *comp;
    }

    Component& Entity::GetComponent(const RTTI& type)
    {
        auto& comp = mComponents[type];

        if (!comp)
        {
            _ASSERT_EXPR(false, "Component does not exist");
        }

        return *comp;
    }
}
