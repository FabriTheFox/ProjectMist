#include "MistEngine_PCH.h"

#include <Engine/MistEngine.h>

namespace ME
{
    MistEngine::MistEngine() 
        : Window(*this)
        , Graphics(*this)
        , EntitySystem(*this)
        , InputSystem(*this)
    {
    }

    void MistEngine::Initialize()
    {
        Window.OnInitialize();
        Graphics.OnInitialize();
        EntitySystem.OnInitialize();
        InputSystem.OnInitialize();
    }

    void MistEngine::Update()
    {
        Window.OnUpdate();
        InputSystem.OnUpdate();

        EntitySystem.OnUpdate();

        Graphics.OnUpdate();
        Graphics.Render();
    }

    void MistEngine::ShutDown()
    {
        InputSystem.OnShutdown();
        EntitySystem.OnShutdown();
        Graphics.OnShutdown();
        Window.OnShutdown();
    }
}