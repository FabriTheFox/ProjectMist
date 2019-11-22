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
    class MistEngine;

    class MISTENGINE_DLL Entity : public IDynamic
    {
        RTTI_DECLARATION(Entity);
        NON_COPYABLE(Entity);

        friend class EntitySystem;

    public:
        Entity(MistEngine* engine = nullptr, const String& name = "");
        ~Entity();

        Component& AddComponent(const RTTI& type);
        Component& GetComponent(const RTTI& type);

        template <typename T>
        T& GetComponent()
        {
            auto& comp = mComponents[T::sGetRTTI()];

            if (!comp)
            {
                _ASSERT_EXPR(false, "Component does not exist");
            }

            return *static_cast<T*>(comp);
        }

    public:
        Transform3D mTransform;

    protected:
        MistEngine* mEngine{ nullptr };

    private:
        void OnEntityInitialize();
        void OnEntityUpdate();
        void OnEntityPredestroy();

        virtual void OnInitialize() {}
        virtual void OnUpdate() {}
        virtual void OnPredestroy() {}

        String mName;
        UnorderedMap<RTTI, Component*> mComponents;
    };
}