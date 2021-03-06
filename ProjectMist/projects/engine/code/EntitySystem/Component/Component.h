#pragma once

#include <RTTI/RTTI.h>
#include <Engine/ClassQualifiers/ClassQualifiers.h>
#include <Libraries/Memory.h>
#include <Engine/MistEngineDefs.h>
#include <Transform/Transform.h>

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
        virtual void OnPredestroy() {}

        virtual void OnUpdate() {}

        bool IsMarkedForDeletion() { return mMarkedForDelete; }
        Entity* GetOwner() { return mOwner; }
        Transform3D& GetTransform();

    private:
        void MarkForDeletion() { mMarkedForDelete = true; }

        Entity* mOwner{nullptr};
        bool mMarkedForDelete{ false };
    };
}