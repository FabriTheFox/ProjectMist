#pragma once

#include <Engine/MistEngine.h>
#include <Engine/Singleton.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>

namespace ME
{
    class MISTENGINE_DLL Event
    {

    };

    class MISTENGINE_DLL EventDispatcher
    {
    public:
        virtual void OnEvent(Event* ev) 
        {
            OnEvent();
        }
    };

    class MISTENGINE_DLL EventSystem
    {
        SINGLETON_DEFCTOR(EventSystem);
    public:

        template <typename T >
        void DispatchEvent(const T& event)
        {
            m_Listeners->OnEvent<T>(event);
        }

        UnorderedMap<>* m_Listeners;
    };
}