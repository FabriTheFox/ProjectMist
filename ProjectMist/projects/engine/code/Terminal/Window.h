#pragma once

#include <Engine/MistEngine.h>
#include <Libraries/Containers.h>

namespace ME
{
    class Window
    {
    public:
        MISTENGINE_DLL Window();

        MISTENGINE_DLL void CreateTheWindow();

        void SetWindowName(const String& name);
        const String& GetWindowName();

        void ProcessWindowMessages();

    private:
        String m_WindowName;
        void* m_WindowHandle;
    };
}

