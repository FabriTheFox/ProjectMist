#include <Engine/MistEngineDefs.h>
#include <Terminal/Terminal.h>
#include <EventSystem/EventSystem.h>

#include <Windows.h>

#include <iostream>

#include <vector>

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

int main()
{
    auto& t = ME::Terminal::GetInstance();
    t.GetWindow().SetWindowName("Liya");
    auto& w = t.GetWindow();
    w.CreateTheWindow();

    auto& evs = ME::EventSystem::GetInstance();
    ListeningClass ExplosionListener;

    //evs.RegisterListener<ExplosionEvent>(std::bind(&ListeningClass::OnExplosionEvent, ExplosionListener, std::placeholders::_1));
    //evs.RegisterListener<ExplosionEvent>(std::bind(&ListeningClass::OnExplosionEvent2, ExplosionListener, std::placeholders::_1));

    evs.RegisterListener(&ListeningClass::OnExplosionEvent, &ExplosionListener);
    evs.RegisterListener(&ListeningClass::OnExplosionEvent2, &ExplosionListener);

    evs.RegisterListener(&globalOnExplosion);

    ExplosionEvent explosion;
    explosion.name = "BOOM";

    //evs.UnRegisterListener<ExplosionEvent>(&ListeningClass::OnExplosionEvent, &ExplosionListener);
    //evs.UnRegisterListener(&globalOnExplosion);

    evs.UnRegisterAllListenersOfEvent(explosion.GetRTTI());

    evs.DispatchEvent(explosion);
    evs.DispatchEvent(explosion);

    while (true)
    {
        w.ProcessWindowMessages();
    }

    return 0;
}
