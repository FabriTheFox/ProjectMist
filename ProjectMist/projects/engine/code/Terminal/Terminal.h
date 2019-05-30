#pragma once

#include <Engine/MistEngineDefs.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>
#include <Graphics/Graphics.h>

#include "Window.h"

namespace ME
{
    class MISTENGINE_DLL Terminal : public System
    {
        SYSTEM_DECLARATION(Terminal);

    public:
        ME::Window& GetWindow();

    private:
        Window m_Window;
    };
}
