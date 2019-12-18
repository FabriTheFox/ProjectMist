#include "MistEngine_PCH.h"

#include "RendererComp.h"

#include <Graphics/DeviceResources.h>
#include <d3dcompiler.h>

#include <Engine/MistEngine.h>
#include <Graphics/Graphics.h>

#include <Graphics/Model/Model.h>
#include <Graphics/Shader/Shader.h>
#include <BuiltInAssets/Shaders/Shaders.h>
#include <Graphics/VertexLayout/VertexLayout.h>
#include "EntitySystem/Component/Component.h"
#include "EntitySystem/EntitySystem.h"
#include "EntitySystem/Entity/Entity.h"

#include "Transform/Camera/Camera.h"

namespace ME
{
    RTTI_IMPLEMENTATION(RendererComp);

    void RendererComp::OnRegister(MistEngine& engine)
    {
        engine.Graphics.RegisterComponent(this);

        mModel = new Model;
        mShader = new ColorShader();

        mModel->Create(engine.Graphics.mDeviceResources.m_pd3dDevice);

        auto* vs = new VertexShader();
        auto* ps = new PixelShader();
        vs->Create(engine.Graphics.mDeviceResources.m_pd3dDevice, "", mModel->mVertexLayout);
        ps->Create(engine.Graphics.mDeviceResources.m_pd3dDevice, "");

        mShader->SetVertexShader(vs);
        mShader->SetPixelShader(ps);
        mShader->CreateConstantBuffers(engine.Graphics.mDeviceResources.m_pd3dDevice);
    }

    void RendererComp::OnUnregister(MistEngine& engine)
    {
        UNUSED_PARAM(engine);
    }

    void RendererComp::OnInitialize()
    {

    }

    void RendererComp::OnDestroy()
    {

    }

    void RendererComp::OnUpdate()
    {
        
    }

    void RendererComp::Render(DeviceResources* dev)
    {
        mShader->Draw(dev, this);
    }

    // -----------------------------------------------------------------------------------------
    RTTI_IMPLEMENTATION(BasicEffectRend);

    void BasicEffectRend::Render(DeviceResources* dev)
    {
        DirectX::BasicEffect be(dev->m_pd3dDevice);

        be.SetDiffuseColor({1, 0, 0, 1});
        be.SetEmissiveColor({ {0, 0, 0, 1} });
        be.SetSpecularColor({ 0, 0, 0, 1 });
        be.SetSpecularPower(1.f);
        be.DisableSpecular();
        be.SetAlpha(1.f);

        be.SetLightingEnabled(false);
        be.SetPerPixelLighting(false);
        be.SetAmbientLightColor({ 1, 1, 1, 1 });

        auto world = GetOwner()->mTransform.GetMatrix();
        be.SetWorld(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&world)));

        auto view = mCamera->GetViewMatrix();
        be.SetView(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&view)));

        auto proj = mCamera->GetProjectionMatrix();
        be.SetProjection(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&proj)));

        be.Apply(dev->m_pd3dDeviceContext);
    }
}

