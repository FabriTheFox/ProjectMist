#pragma once

#include <Engine/MistEngineDefs.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>

namespace ME
{
    class Entity;
    class MistEngine;

    class MISTENGINE_DLL EntitySystem : public System
    {
        SYSTEM_DECLARATION(EntitySystem);

    public:
        void OnInitialize() override final;
        void OnUpdate() override final;

        Entity& CreateEntity(const String& name = "");

        template <typename T>
        T& CreateEntity(const String& name = "")
        {
            mEntities.emplace_back(new T(&GetEngine(), name));
            return *(static_cast<T*>(mEntities.back()));
        }

    private:
        Vector<Entity*> mEntities;
    };
}
