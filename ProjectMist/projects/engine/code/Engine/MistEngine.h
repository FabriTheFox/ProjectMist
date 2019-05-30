#pragma once

#include <Engine/ClassAttributes/ClassAttributes.h>

#include <Graphics/Graphics.h>
#include <Terminal/Terminal.h>
#include <EntitySystem/EntitySystem.h>

namespace ME
{
    class MISTENGINE_DLL MistEngine
    {
        NON_COPYABLE(MistEngine);
    public:
        MistEngine();

        Graphics Graphics;
        Terminal Terminal;
        EntitySystem EntitySystem;

    private:
    };
}