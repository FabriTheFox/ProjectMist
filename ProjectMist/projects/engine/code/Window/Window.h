#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>
#include <Graphics/DeviceResources.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>

#include <Window/Terminal.h>

namespace ME
{
    class MISTENGINE_DLL Window : public System
    {
        SYSTEM_DECLARATION(Window);

    public:
        Window();

        void CreateTheWindow();

        void SetWindowName(const String& name);
        const String& GetWindowName();

        void ProcessWindowMessages();

        Terminal mTerminal;

    //private:
        String m_WindowName;
        void* m_WindowHandle;

        DeviceResources* dr;
    };
}

