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
}

