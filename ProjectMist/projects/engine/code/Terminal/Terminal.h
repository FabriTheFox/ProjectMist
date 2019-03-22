#pragma once

#include <Engine/MistEngineDefs.h>
#include <Engine/Singleton.h>
#include <RTTI/RTTI.h>

#include "Window.h"

namespace ME
{
    class Terminal 
    {
        RTTI_DECLARATION(Terminal);
        SINGLETON_DEFCTOR_DLL(Terminal, MISTENGINE_DLL);

    public:

        MISTENGINE_DLL ME::Window& GetWindow();

    private:
        Window m_Window;
    };
}
