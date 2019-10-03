#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <Graphics/DeviceResources.h>

struct ID3D11Device;
class DeviceResources;


namespace ME
{
    class RendererComp;
    class Camera;

    class MISTENGINE_DLL Graphics : public System
    {
        SYSTEM_DECLARATION(Graphics);
        friend class RendererComp;
    public:

        void Initialize();
        void Update();
        void Render();

        Camera* mCamera;

    private:
        void RegisterComponent(RendererComp* renderer);
        CompPointerVector mRenderables;

        DeviceResources mDeviceResources;
    };
}
