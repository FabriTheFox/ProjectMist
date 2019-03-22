#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>

namespace ME
{
    class Window
    {
    public:
        MISTENGINE_DLL Window();

        MISTENGINE_DLL void CreateTheWindow();

        MISTENGINE_DLL void SetWindowName(const String& name);
        MISTENGINE_DLL const String& GetWindowName();

        MISTENGINE_DLL void ProcessWindowMessages();

    private:
        String m_WindowName;
        void* m_WindowHandle;
    };
}

