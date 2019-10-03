#include "Entity.h"
#include <EntitySystem/Component/Component.h>
#include <EntitySystem/EntitySystem.h>

namespace ME
{
    RTTI_IMPLEMENTATION(Entity);

    Entity::Entity(EntitySystem* entitysys, const String& name)
        : mEntitySystem(entitysys)
        , mName(name)
    {
    }

    Entity::~Entity()
    {
        for (auto& comp : mComponents)
        {
            comp.second->MarkForDeletion();
        }
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

        comp->OnRegister(mEntitySystem->GetEngine());

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
