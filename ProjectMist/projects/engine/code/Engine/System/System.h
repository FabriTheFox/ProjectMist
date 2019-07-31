#pragma once

#include <Engine/ClassQualifiers/ClassQualifiers.h>
#include <RTTI/RTTI.h>

#include <Engine/MistEngineDefs.h>

namespace ME
{
    class MistEngine;

    class MISTENGINE_DLL System
    {
        NON_COPYABLE(System);

    public:
        System(MistEngine& engine) : mEngine(engine) {}
        System() = delete;

        MistEngine& GetEngine() { return mEngine; }

    protected:
        MistEngine& mEngine;
    };

    class Component;
    class CompPointerVector
    {
    public:
        void Register(Component* ptr);
        
        template<typename T>
        T* GetComponentAt(unsigned index) const
        {
            return mComponents[index];
        }
    
        void DeleteDead();

        Vector<Component*> mComponents;
    };
}

#define SYSTEM_DECLARATION(thistype)                                \
    public : thistype(MistEngine& me) : System(me){} private: