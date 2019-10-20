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
    
    auto& g = e.Graphics;
    g.mCamera = new ME::Camera;

    auto& es = e.EntitySystem;
    auto& en = es.CreateEntity("Liya");
    auto& en2 = es.CreateEntity("Liya2");

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
        e.Window.Update();
        e.InputSystem.Update();

        if (e.InputSystem.IsKeyIdle('A'))
        {
            std::cout << "Idle" << std::endl;
        }
        if (e.InputSystem.IsKeyTriggered('A'))
        {
            std::cout << "Triggered" << std::endl;
        }
        if (e.InputSystem.IsKeyPressed('A'))
        {
            std::cout << "Pressed" << std::endl;
        }
        if (e.InputSystem.IsKeyReleased('A'))
        {
            std::cout << "Released" << std::endl;
        }


        //if (t.mTerminal.IsKeyUp(VK_LBUTTON))
        //{
        //    std::cout << "Key up" << std::endl;
        //}

        g.Update();
        g.Render();

        Sleep(16);
    }

    e.ShutDown();

    return 0;
}
