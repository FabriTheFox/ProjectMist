#pragma once

#include <EntitySystem/Component/Component.h>

#include <d3d11_4.h>
#include <DirectXMath.h>

namespace ME
{
    class DeviceResources;
    class Model;
    class ShaderProgram;

    class MISTENGINE_DLL RendererComp : public Component
    {
        RTTI_DECLARATION(RendererComp);
    public:
        void OnRegister(MistEngine& engine) override final;
        void OnUnregister(MistEngine& engine) override final;

        void OnInitialize();
        void OnDestroy();
        void OnUpdate();

        void Render(DeviceResources* dev);

    public:
        Model* mModel = nullptr;
        ShaderProgram* mShader = nullptr;
    };
}