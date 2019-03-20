#pragma once

#include <Engine/MistEngine.h>
#include <Engine/Singleton.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>

namespace ME
{
    class Event
    {

    };

    class EventListener
    {
        template <typename T>
        virtual void OnEvent(const T& ev) {}
    };

    class EventSystem
    {
        SINGLETON_DEFCTOR(EventSystem);
    public:

        ME::Map<Event, ME::Vector<ME::WPtr<EventListener>>> m_Listeners;
    };
}