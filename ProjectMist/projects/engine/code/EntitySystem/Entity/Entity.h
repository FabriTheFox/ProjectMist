#pragma once

#include <RTTI/RTTI.h>
#include <Engine/ClassAttributes/ClassAttributes.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>
#include <Engine/MistEngineDefs.h>

namespace ME
{
    class Component;
    class EntitySystem;

    class MISTENGINE_DLL Entity : public IDynamic
    {
        RTTI_DECLARATION(Entity);
        NON_COPYABLE(Entity);

    public:
        Entity(EntitySystem* entitysys = nullptr, const String& name = "");
        ~Entity();

        const Component& AddComponent(const RTTI& type);
        const Component& GetComponent(const RTTI& type);

    private:
        EntitySystem * mEntitySystem{nullptr};
        String mName;
        UnorderedMap<RTTI, Component*> mComponents;
    };
}