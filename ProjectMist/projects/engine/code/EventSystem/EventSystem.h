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
        void RegisterListener(void (Obj::*lisfunc)(const Ev&), Obj* instance)
        {
            auto& disp = m_Dispatchers[Ev::sGetRTTI()];
            disp.push_back(std::make_unique<EventDispatcher<Ev, Obj>>(lisfunc, instance));
        }

        template <typename Ev>
        void UnRegisterListener(void* lisfunc, void* instance = nullptr)
        {
            auto& itr = m_Dispatchers.find(Ev::sGetRTTI());
            if (itr == m_Dispatchers.end())
                return;
            for (auto& d : itr->second)
            {
                if (d->IsSameAs(lisfunc, instance))
                {
                    d = itr->second.back();
                    itr->second.pop_back();
                    return;
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
        public:
            virtual void Dispatch(Event* theevent) = 0;
            virtual void* GetObjectInstance() const = 0;
            virtual void* GetFunctionPtr() const = 0;
            bool IsSameAs(void* funct, void* obj) { return GetObjectInstance() == obj && GetFunctionPtr() == funct; }
        };

        template<typename Ev, typename Obj>
        class EventDispatcher : public IEventDispatcher
        {
        public:
            typedef void (Obj::*ListenerFunc)(const Ev&);
            EventDispatcher(void (Obj::*lisfunc)(const Ev&), Obj* instance) : m_Function(lisfunc) {}

            void* GetObjectInstance() const override final { return m_Instance; }
            virtual void* GetFunctionPtr() const override final { return m_Function; }

            void Dispatch(Event* theevent) override final 
            { 
                (m_Instance->*m_Function)(*((Ev*)theevent));
            }

        private:
            Obj* m_Instance;
            ListenerFunc m_Function;
        };

        using DispatcherArray = std::vector<Uptr<IEventDispatcher>>;
        std::map<RTTI, DispatcherArray> m_Dispatchers;
    };

    RTTI_IMPLEMENTATION(EventSystem);
}