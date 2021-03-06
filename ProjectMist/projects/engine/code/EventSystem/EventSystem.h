#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>
#include <Libraries/Memory.h>
#include <RTTI/RTTI.h>

#include <functional>

namespace ME
{
    class Event : public IDynamic
    {
        RTTI_DECLARATION_DLL(Event, MISTENGINE_DLL);
    };

    class EventSystem
    {
    public:
        template <typename Ev, typename Obj>
        void RegisterListener(void (Obj::*listener)(const Ev&), Obj* instance)
        {
            auto& disp = m_Dispatchers[Ev::sGetRTTI()];
            disp.push_back(std::make_unique<EventDispatcherMember<Ev, Obj>>(listener, instance));
        }

        template <typename Ev, typename Obj>
        void RegisterListener(void (Obj::*listener)(const Ev&), WPtr<Obj> instance)
        {
            auto& disp = m_Dispatchers[Ev::sGetRTTI()];
            disp.push_back(std::make_unique<EventDispatcherMemberWk<Ev, Obj>>(listener, instance));
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

        template <typename Ev, typename Obj>
        void UnRegisterListener(void (Obj::*listener)(const Ev&), WPtr<Obj> instance)
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            const auto& rtti = EventDispatcherMemberWk<Ev, Obj>::sGetRTTI();
            for (auto& d : itr->second)
            {
                if (d->GetRTTI() == rtti)
                {
                    auto& disp = *((EventDispatcherMemberWk<Ev, Obj>*)d.get());
                    if (disp.m_Function == listener && (disp.m_Instance.expired() || disp.m_Instance.lock().get() == instance.lock().get()))
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
        void DispatchEvent(const Ev& theevent) const
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            for (auto& d : itr->second)
                d->Dispatch((Event*)&theevent);
        }

    private:
        void CleanAllExpired()
        {
            for (auto& list : m_Dispatchers) for (auto& d : list.second)
            {
                if (d->Expired())
                {
                    d = std::move(list.second.back());
                    list.second.pop_back();
                }
            }
        }

        class IEventDispatcher : public IDynamic
        {
        public:
            virtual bool Dispatch(Event* theevent) const = 0;
            virtual bool Expired() const { return false; }
        };

        template <typename Ev, typename Obj>
        class EventDispatcherMember : public IEventDispatcher
        {
            RTTI_DECLARATION_DLL(EventDispatcherMember, MISTENGINE_DLL);
        public:
            typedef void (Obj::*ListenerFunc)(const Ev&);
            EventDispatcherMember() = default;
            EventDispatcherMember(ListenerFunc listener, Obj* instance) : m_Function(listener), m_Instance(instance) {}
            bool Dispatch(Event* theevent) const override final { (m_Instance->*m_Function)(*((Ev*)theevent)); return true; }

            Obj* m_Instance;
            ListenerFunc m_Function;
        };

        template <typename Ev, typename Obj>
        class EventDispatcherMemberWk : public IEventDispatcher
        {
            RTTI_DECLARATION_DLL(EventDispatcherMemberWk, MISTENGINE_DLL);
        public:
            typedef void (Obj::*ListenerFunc)(const Ev&);
            EventDispatcherMemberWk() = default;
            EventDispatcherMemberWk(ListenerFunc listener, WPtr<Obj> instance) : m_Function(listener), m_Instance(instance) {}
            bool Dispatch(Event* theevent) const override final
            {
                if (m_Instance.expired())
                    return false;
                ((m_Instance.lock().get())->*m_Function)(*((Ev*)theevent));
                return true;
            }
            bool Expired() const override final { return m_Instance.expired(); }

            WPtr<Obj> m_Instance;
            ListenerFunc m_Function;
        };

        template <typename Ev>
        class EventDispatcher : public IEventDispatcher
        {
            RTTI_DECLARATION_DLL(EventDispatcher, MISTENGINE_DLL);
        public:
            typedef void (*ListenerFunc)(const Ev&);
            EventDispatcher() = default;
            EventDispatcher(ListenerFunc listener) : m_Function(listener) {}
            bool Dispatch(Event* theevent) const override final { (m_Function)(*((Ev*)theevent)); return true; }

            ListenerFunc m_Function;
        };

        using DispatcherArray = std::vector<UPtr<IEventDispatcher>>;
        std::map<RTTI, DispatcherArray> m_Dispatchers;
    };

    RTTI_IMPLEMENTATION_TEMPLATE(EventSystem::EventDispatcherMember, Ev, Obj);
    RTTI_IMPLEMENTATION_TEMPLATE(EventSystem::EventDispatcherMemberWk, Ev, Obj);
    RTTI_IMPLEMENTATION_TEMPLATE(EventSystem::EventDispatcher, Ev);
}