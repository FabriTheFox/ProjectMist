#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>

#include <Graphics/DeviceResources.h>

namespace ME
{
    class MISTENGINE_DLL Window
    {
    public:
        Window();

        void CreateTheWindow();

        void SetWindowName(const String& name);
        const String& GetWindowName();

        void ProcessWindowMessages();

    //private:
        String m_WindowName;
        void* m_WindowHandle;

        DeviceResources* dr;
    };
}

