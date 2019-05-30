#pragma once

#include <Engine/MistEngineDefs.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>

#include <Libraries/Containers.h>
#include <Libraries/Memory.h>

namespace ME
{
    class Entity;

    class MISTENGINE_DLL EntitySystem : public System
    {
        SYSTEM_DECLARATION(EntitySystem);

    public:
        void Initialize();
        void Update();

        Entity& CreateEntity(const String& name = "");

    private:
        Vector<Entity*> mEntities;
    };
}
