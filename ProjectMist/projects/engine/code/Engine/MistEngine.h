#pragma once

#include <Engine/ClassQualifiers/ClassQualifiers.h>

#include <Graphics/Graphics.h>
#include <Window/Window.h>
#include <EntitySystem/EntitySystem.h>
#include <InputSystem/InputSystem.h>

namespace ME
{
    class MISTENGINE_DLL MistEngine
    {
        NON_COPYABLE(MistEngine);
    public:
        MistEngine();

        void Initialize();
        void Update();
        void ShutDown();

        Graphics Graphics;
        Window Window;
        EntitySystem EntitySystem;
        InputSystem InputSystem;

    private:
    };
}