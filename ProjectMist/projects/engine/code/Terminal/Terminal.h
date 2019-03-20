#pragma once

#include <Engine/MistEngine.h>
#include <Engine/Singleton.h>

#include "Window.h"

namespace ME
{
    class Terminal
    {
        SINGLETON_DEFCTOR(Terminal);
    public:

        MISTENGINE_DLL ME::Window& GetWindow();

    private:
        Window m_Window;
    };
}
