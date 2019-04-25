#pragma once

#include <EventSystem/EventSystem.h>
#include <iostream>

class ExplosionEvent : public ME::Event
{
    RTTI_DECLARATION(ExplosionEvent)
public:
    ME::String name;
};

RTTI_IMPLEMENTATION(ExplosionEvent)

class ListeningClass
{
public:
    void OnExplosionEvent(const ExplosionEvent& explo)
    {
        std::cout << explo.name << std::endl;
    }

    void OnExplosionEvent2(const ExplosionEvent& explo)
    {
        std::cout << explo.name << "(again)" << std::endl;
    }
};

void globalOnExplosion(const ExplosionEvent& explo)
{
    std::cout << explo.name << "(global)" << std::endl;
}

void TestEvents()
{
    auto& evs = ME::EventSystem::GetInstance();
    ME::Ptr<ListeningClass> ExplosionListener = std::make_shared<ListeningClass>();

    ME::WPtr<ListeningClass> lis = ExplosionListener;

    evs.RegisterListener(&ListeningClass::OnExplosionEvent, lis);
    evs.RegisterListener(&ListeningClass::OnExplosionEvent2, lis);

    //evs.RegisterListener(&globalOnExplosion);

    ExplosionEvent explosion;
    explosion.name = "BOOM";

    //evs.UnRegisterListener(&ListeningClass::OnExplosionEvent, lis);

    //evs.UnRegisterListener<ExplosionEvent>(&ListeningClass::OnExplosionEvent, &ExplosionListener);
    //evs.UnRegisterListener(&globalOnExplosion);

    //evs.UnRegisterAllListenersOfEvent(explosion.GetRTTI());

    evs.DispatchEvent(explosion);
    evs.DispatchEvent(explosion);
}