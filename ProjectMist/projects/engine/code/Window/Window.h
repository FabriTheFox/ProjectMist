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
        void OnInitialize() override final;
        void OnUpdate() override final;
        void OnShutdown() override final;

        void SetWindowName(const String& name);

        const String& GetWindowName() { return mWindowName; }
        void* GetWindowHandle() { return mWindowHandle; }

        Terminal mTerminal;

    private:
        void CreateTheWindow();
        void ProcessWindowMessages();

        String mWindowName;
        void* mWindowHandle;

        DeviceResources* mDeviceResources;
    };
}

