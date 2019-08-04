#pragma once

#include <RTTI/RTTI.h>
#include <Engine/ClassQualifiers/ClassQualifiers.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>
#include <Engine/MistEngineDefs.h>
#include <Transform/Transform.h>

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

    public:
        Transform3D mTransform;

    private:
        EntitySystem * mEntitySystem{nullptr};
        String mName;
        UnorderedMap<RTTI, Component*> mComponents;
    };
}