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
        template <typename Ev>
        void RegisterListener(std::function<void(const Ev&)> listener)
        {
            auto& disp = m_Dispatchers[Ev::sGetRTTI()];
            disp.push_back(std::make_unique<EventDispatcher<Ev>>(listener));
        }

        template <typename Ev>
        void UnRegisterListener(std::function<void(const Ev&)> listener)
        {
            auto itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            const auto& rtti = EventDispatcher<Ev>::sGetRTTI();
            for (auto& d : itr->second)
            {
                if (d->GetRTTI() == rtti)
                {
                    if (((EventDispatcher<Ev>*)d.get())->m_Function.target_type() == listener.target_type())
                    {
                        d = std::move(itr->second.back());
                        itr->second.pop_back();
                        return;
                    }
                }
            }
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

        template<typename Ev>
        class EventDispatcher : public IEventDispatcher
        {
            RTTI_DECLARATION(EventDispatcher);
        public:
            typedef std::function<void(const Ev&)> ListenerFunc;
            EventDispatcher(ListenerFunc listener) : m_Function(listener) {}

            void Dispatch(Event* theevent) override final 
            { 
                m_Function(*((Ev*)theevent));
            }

        //private:
            ListenerFunc m_Function;
        };

        using DispatcherArray = std::vector<Uptr<IEventDispatcher>>;
        std::map<RTTI, DispatcherArray> m_Dispatchers;
    };

    RTTI_IMPLEMENTATION(EventSystem);
    RTTI_IMPLEMENTATION(EventSystem::IEventDispatcher);

    template <typename Ev>
    RTTI_IMPLEMENTATION(EventSystem::EventDispatcher<Ev>);
}