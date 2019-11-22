#include <Engine/MistEngineDefs.h>
#include <Window/Terminal.h>
#include <EventSystem/EventSystem.h>

#include <Windows.h>

#include <iostream>

#include <vector>

#include "TestEvents.h"
#include <Engine/MistEngine.h>

#include <Libraries/Containers.h>
#include <EntitySystem/Entity/Entity.h>

#include <Graphics/RendererComp/RendererComp.h>

#include <Transform/Camera/Camera.h>
#include <Transform/Camera/FreeCamera.h>

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
    e.Initialize();

    auto& t = e.Window;
    t.SetWindowName("Liya");

    auto& es = e.EntitySystem;
    auto& en = es.CreateEntity("Liya");
    auto& en2 = es.CreateEntity("Liya2");

    auto& g = e.Graphics;
    g.mCamera = &es.CreateEntity<ME::FreeCamera>("MainCamera");

    en.mTransform.mPosition.x = 1;
    en2.mTransform.mPosition.x = -1;

    en.AddComponent(ME::RendererComp::sGetRTTI());
    auto& rcmp = en.GetComponent<ME::RendererComp>();
    rcmp.mCamera = g.mCamera;

    en2.AddComponent(ME::RendererComp::sGetRTTI());
    auto& rcmp2 = en2.GetComponent<ME::RendererComp>();
    rcmp2.mCamera = g.mCamera;

    while (true)
    {
        e.Update();
        Sleep(16);
    }

    e.ShutDown();

    return 0;
}
