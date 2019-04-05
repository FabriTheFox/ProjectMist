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

    class EventSystem
    {
        RTTI_DECLARATION(EventSystem);
        SINGLETON_DEFCTOR(EventSystem);

    public:
        template <typename Ev, typename Obj>
        void RegisterListener(void (Obj::*listener)(const Ev&), Obj* instance)
        {
            auto& disp = m_Dispatchers[Ev::sGetRTTI()];
            disp.push_back(std::make_unique<EventDispatcherMember<Ev, Obj>>(listener, instance));
        }

        template <typename Ev>
        void RegisterListener(void (*listener)(const Ev&))
        {
            auto& disp = m_Dispatchers[Ev::sGetRTTI()];
            disp.push_back(std::make_unique<EventDispatcher<Ev>>(listener));
        }

        template <typename Ev, typename Obj>
        void UnRegisterListener(void (Obj::*listener)(const Ev&), Obj* instance)
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            const auto& rtti = EventDispatcherMember<Ev, Obj>::sGetRTTI();
            for (auto& d : itr->second)
            {
                if (d->GetRTTI() == rtti)
                {
                    auto& disp = *((EventDispatcherMember<Ev, Obj>*)d.get());
                    if (disp.m_Function == listener && disp.m_Instance == instance)
                    {
                        d = std::move(itr->second.back());
                        itr->second.pop_back();
                        return;
                    }
                }
            }
        }

        template <typename Ev>
        void UnRegisterListener(void (*listener)(const Ev&))
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            const auto& rtti = EventDispatcher<Ev>::sGetRTTI();
            for (auto& d : itr->second)
            {
                if (d->GetRTTI() == rtti)
                {
                    auto& disp = *((EventDispatcher<Ev>*)d.get());
                    if (disp.m_Function == listener)
                    {
                        d = std::move(itr->second.back());
                        itr->second.pop_back();
                        return;
                    }
                }
            }
        }

        template <typename Ev>
        void UnRegisterAllListenersOfEvent()
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            itr->second.clear();
        }

        void UnRegisterAllListenersOfEvent(const RTTI& eventype)
        {
            auto itr = m_Dispatchers.find(eventype);
            if (itr == m_Dispatchers.end())
                return;
            itr->second.clear();
        }

        template <typename Ev>
        void DispatchEvent(const Ev& theevent)
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            for (auto& d : itr->second)
                d->Dispatch((Event*)&theevent);
        }

    private:
        class IEventDispatcher
        {
            RTTI_DECLARATION(IEventDispatcher);
        public:
            virtual void Dispatch(Event* theevent) = 0;
        };

        template <typename Ev, typename Obj>
        class EventDispatcherMember : public IEventDispatcher
        {
            RTTI_DECLARATION(EventDispatcherMember);
        public:
            typedef void (Obj::*ListenerFunc)(const Ev&);
            EventDispatcherMember(ListenerFunc listener, Obj* instance) : m_Function(listener), m_Instance(instance) {}
            void Dispatch(Event* theevent) override final { (m_Instance->*m_Function)(*((Ev*)theevent)); }

            Obj* m_Instance;
            ListenerFunc m_Function;
        };

        template <typename Ev>
        class EventDispatcher : public IEventDispatcher
        {
            RTTI_DECLARATION(EventDispatcher);
        public:
            typedef void (*ListenerFunc)(const Ev&);
            EventDispatcher(ListenerFunc listener) : m_Function(listener) {}
            void Dispatch(Event* theevent) override final { (m_Function)(*((Ev*)theevent)); }

            ListenerFunc m_Function;
        };

        using DispatcherArray = std::vector<Uptr<IEventDispatcher>>;
        std::map<RTTI, DispatcherArray> m_Dispatchers;
    };

    RTTI_IMPLEMENTATION(EventSystem);
    RTTI_IMPLEMENTATION(EventSystem::IEventDispatcher);

    template <typename Ev, typename Obj>
    const ME::RTTI& EventSystem::EventDispatcherMember<Ev, Obj>::sm_RTTI = ME::RTTISystem::RegisterRTTI<EventSystem::EventDispatcherMember<Ev, Obj>>();

    template <typename Ev>
    const ME::RTTI& EventSystem::EventDispatcher<Ev>::sm_RTTI = ME::RTTISystem::RegisterRTTI<EventSystem::EventDispatcher<Ev>>();
}