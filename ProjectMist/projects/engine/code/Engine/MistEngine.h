#pragma once

#include <Engine/ClassQualifiers/ClassQualifiers.h>

#include <Graphics/Graphics.h>
#include <Window/Window.h>
#include <EntitySystem/EntitySystem.h>

namespace ME
{
    class MISTENGINE_DLL MistEngine
    {
        NON_COPYABLE(MistEngine);
    public:
        MistEngine();

        Graphics Graphics;
        Window Window;
        EntitySystem EntitySystem;

    private:
    };
}