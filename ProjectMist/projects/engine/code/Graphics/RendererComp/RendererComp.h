#pragma once

#include <EntitySystem/Component/Component.h>

#include <d3d11_4.h>
#include <DirectXMath.h>

#include <directxtk/inc/Effects.h>

namespace ME
{
    class DeviceResources;
    class Model;
    class ShaderProgram;
    class Camera;

    class MISTENGINE_DLL RendererComp : public Component
    {
        RTTI_DECLARATION(RendererComp);
    public:
        void OnRegister(MistEngine& engine) override final;
        void OnUnregister(MistEngine& engine) override final;

        void OnInitialize();
        void OnDestroy();
        void OnUpdate();

        virtual void Render(DeviceResources* dev);

        Camera* mCamera = nullptr;

    public:
        Model* mModel = nullptr;
        ShaderProgram* mShader = nullptr;
    };

    // -----------------------------------------------------------------------------------------
    class MISTENGINE_DLL BasicEffectRend : public RendererComp
    {
        RTTI_DECLARATION(BasicEffectRend);
    public:
        virtual void Render(DeviceResources* dev) override;
    };
}