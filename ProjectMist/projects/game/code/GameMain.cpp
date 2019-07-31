#include <Engine/MistEngineDefs.h>
#include <Terminal/Terminal.h>
#include <EventSystem/EventSystem.h>

#include <Windows.h>

#include <iostream>

#include <vector>

#include "TestEvents.h"
#include <Engine/MistEngine.h>

#include <Libraries/Containers.h>
#include <EntitySystem/Entity/Entity.h>

#include <Graphics/RendererComp/RendererComp.h>

class lmao
{
public:
    float r;
};

class A
{
public:
    int a;
    static constexpr lmao lm{};
};

class B : public A
{
public:
    int b;
};

int main()
{
    A aa = A();
    float rrr = aa.lm.r;

    ME::MistEngine e;
    auto& t = e.Terminal;
    t.GetWindow().SetWindowName("Liya");
    auto& w = t.GetWindow();
    w.CreateTheWindow();
    
    auto& g = e.Graphics;
    g.Initialize();

    auto& es = e.EntitySystem;
    auto& en = es.CreateEntity("Liya");

    en.AddComponent(ME::RendererComp::sGetRTTI());

    while (true)
    {
        w.ProcessWindowMessages();

        g.Update();
        g.Render();

        Sleep(16);
    }

    return 0;
}
