#pragma once

#include <Engine/MistEngineDefs.h>
#include <Engine/Singleton.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>
#include <RTTI/RTTI.h>

#include <functional>

namespace ME
{
    class Event : public IDynamic
    {
        RTTI_DECLARATION(Event);
    public:
    };

    RTTI_IMPLEMENTATION(Event);

    class IEventDispatcher
    {
    public:
        virtual void Dispatch(Event* theevent) = 0;
    };

    template<typename Ev>
    class EventDispatcher : public IEventDispatcher
    {
    public:
        typedef std::function<void(const Ev&)> ListenerFunc;
        EventDispatcher(ListenerFunc func) : m_func(func) {}

        void Dispatch(Event* theevent) override final
        {
            m_func(*((Ev*)theevent));
        }

        ListenerFunc m_func;
    };

    class EventSystem
    {
        RTTI_DECLARATION(EventSystem);
        SINGLETON_DEFCTOR(EventSystem);

    public:
        template <typename Ev>
        void RegisterListener(std::function<void(const Ev&)> lisfunc)
        {
            auto& disp = m_Dispatchers[Ev.GetRTTI()];
            disp.push_back(std::make_unique<EventDispatcher>(lisfunc));
        }

        template <typename Ev>
        void DispatchEvent(const Ev& theevent)
        {
            auto itr = m_Dispatchers.find(Ev.GetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            for (auto& d : itr->second)
                d->Dispatch(&theevent);
        }

        using DispatcherArray = std::vector<Uptr<IEventDispatcher>>;
        std::map<RTTI, DispatcherArray> m_Dispatchers;
    };

    RTTI_IMPLEMENTATION(EventSystem);
}