#pragma once

#include <RTTI/RTTI.h>
#include <Engine/ClassAttributes/ClassAttributes.h>
#include <Libraries/Memory.h>
#include <Engine/MistEngineDefs.h>

namespace ME
{
    class Entity;
    class MistEngine;

     class MISTENGINE_DLL Component : public IDynamic
    {
        friend class Entity;

    public:
        Component(Entity* owner = nullptr);

        virtual void OnRegister(MistEngine& engine) = 0;
        virtual void OnUnregister(MistEngine& engine) = 0;

        virtual void OnInitialize() {}
        virtual void OnDestroy() {}

        virtual void OnUpdate() {}

        bool IsMarkedForDeletion() { return mMarkedForDelete; };

    private:
        void MarkForDeletion() { mMarkedForDelete = true; }

        Entity* mOwner{nullptr};
        bool mMarkedForDelete{ false };
    };
}