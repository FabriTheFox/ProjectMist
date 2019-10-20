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
        void Initialize() override final;
        void Update() override final;
        void Shutdown() override final;

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

