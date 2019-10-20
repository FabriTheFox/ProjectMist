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
        Window.Initialize();
        Graphics.Initialize();
        EntitySystem.Initialize();
        InputSystem.Initialize();
    }

    void MistEngine::Update()
    {
        //Window.Update();
        //Graphics.Update();
        //EntitySystem.Update();
        //InputSystem.Update();
    }

    void MistEngine::ShutDown()
    {
        InputSystem.Shutdown();
        EntitySystem.Shutdown();
        Graphics.Shutdown();
        Window.Shutdown();
    }
}