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
#include <directxtk/inc/Model.h>
#include "DirectXTK/Inc/VertexTypes.h"

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
        std::shared_ptr<DirectX::BasicEffect> eff = std::make_shared<DirectX::BasicEffect>(dev->m_pd3dDevice);
        DirectX::BasicEffect& be = *eff;

        be.SetDiffuseColor({1, 1, 1, 1});
        be.SetEmissiveColor({ {0, 0, 0, 1} });
        be.SetSpecularColor({ 1, 1, 1, 1 });
        be.SetSpecularPower(1.f);
        be.DisableSpecular();
        be.SetAlpha(1.f);

        be.SetLightingEnabled(true);
        be.SetPerPixelLighting(true);
        be.SetAmbientLightColor({ 0, 0, 0, 1 });
        be.SetVertexColorEnabled(false);

        be.SetLightEnabled(1, true);
        be.SetLightDirection(1, { -1, -1, -1 });
        be.SetLightDiffuseColor(1, { 1, 1, 1 });
        be.SetLightSpecularColor(1, { 1, 1, 1 });

        auto world = GetOwner()->mTransform.GetMatrix();
        be.SetWorld(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&world)));

        auto view = mCamera->GetViewMatrix();
        be.SetView(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&view)));

        auto proj = mCamera->GetProjectionMatrix();
        be.SetProjection(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&proj)));

        be.Apply(dev->m_pd3dDeviceContext);

        // ------------------------------------------------------------------------------------

        HRESULT hr = S_OK;
        ID3D11Buffer* mVertexBuffer = nullptr;
        ID3D11Buffer* mIndexBuffer = nullptr;
        unsigned int mIndexCount = 0;
        unsigned int mVertexCount = 0;
        unsigned int mVertexSize = 0;

        // Create cube geometry.
        //DirectX::VertexPositionNormalColor CubeVertices[] =
        //{
        //{ DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(0,   0,   0, 1), },
        //{ DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(0,   0,   1, 1), },
        //{ DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(0,   1,   0, 1), },
        //{ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(0,   1,   1, 1), },
        //
        //{ DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(1,   0,   0, 1), },
        //{ DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(1,   0,   1, 1), },
        //{ DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(1,   1,   0, 1), },
        //{ DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.5f,0.5f,0.5f), DirectX::XMFLOAT4(1,   1,   1, 1), },
        //};

        DirectX::VertexPositionNormalColor CubeVertices[] =
        {
        { DirectX::XMFLOAT3(-0.5, -0.5, +0.5), DirectX::XMFLOAT3(0.0, 0.0, 1.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, +0.5), DirectX::XMFLOAT3(0.0, 0.0, 1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, +0.5), DirectX::XMFLOAT3(0.0, 0.0, 1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, +0.5), DirectX::XMFLOAT3(0.0, 0.0, 1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, +0.5), DirectX::XMFLOAT3(0.0, 0.0, 1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, +0.5), DirectX::XMFLOAT3(0.0, 0.0, 1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, +0.5), DirectX::XMFLOAT3(1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, -0.5), DirectX::XMFLOAT3(1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, -0.5), DirectX::XMFLOAT3(1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, +0.5), DirectX::XMFLOAT3(1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, -0.5), DirectX::XMFLOAT3(1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, +0.5), DirectX::XMFLOAT3(1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, -0.5), DirectX::XMFLOAT3(0.0, 0.0, -1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, -0.5), DirectX::XMFLOAT3(0.0, 0.0, -1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, -0.5), DirectX::XMFLOAT3(0.0, 0.0, -1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, -0.5), DirectX::XMFLOAT3(0.0, 0.0, -1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, -0.5), DirectX::XMFLOAT3(0.0, 0.0, -1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, -0.5), DirectX::XMFLOAT3(0.0, 0.0, -1.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, -0.5), DirectX::XMFLOAT3(-1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, +0.5), DirectX::XMFLOAT3(-1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, +0.5), DirectX::XMFLOAT3(-1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, -0.5), DirectX::XMFLOAT3(-1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, +0.5), DirectX::XMFLOAT3(-1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, -0.5), DirectX::XMFLOAT3(-1.0, 0.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, +0.5), DirectX::XMFLOAT3(0.0, 1.0, 0.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, +0.5), DirectX::XMFLOAT3(0.0, 1.0, 0.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, -0.5), DirectX::XMFLOAT3(0.0, 1.0, 0.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, +0.5), DirectX::XMFLOAT3(0.0, 1.0, 0.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, +0.5, -0.5), DirectX::XMFLOAT3(0.0, 1.0, 0.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, +0.5, -0.5), DirectX::XMFLOAT3(0.0, 1.0, 0.0), DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, -0.5), DirectX::XMFLOAT3(0.0, -1.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, -0.5), DirectX::XMFLOAT3(0.0, -1.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, +0.5), DirectX::XMFLOAT3(0.0, -1.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, -0.5), DirectX::XMFLOAT3(0.0, -1.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(+0.5, -0.5, +0.5), DirectX::XMFLOAT3(0.0, -1.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)},
        { DirectX::XMFLOAT3(-0.5, -0.5, +0.5), DirectX::XMFLOAT3(0.0, -1.0, 0.0),DirectX::XMFLOAT4(1, 1, 1, 1)}
        };

        // Create vertex buffer:

        CD3D11_BUFFER_DESC vDesc(
            sizeof(CubeVertices),
            D3D11_BIND_VERTEX_BUFFER
        );

        D3D11_SUBRESOURCE_DATA vData;
        ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
        vData.pSysMem = CubeVertices;
        vData.SysMemPitch = 0;
        vData.SysMemSlicePitch = 0;

        hr = dev->m_pd3dDevice->CreateBuffer(
            &vDesc,
            &vData,
            &mVertexBuffer
        );

        // Create index buffer:
        unsigned short CubeIndices[] =
        {
            0,2,1, // -x
            3,5,4,

            6,8,7, // +x
            9,11,10,

            12,14,13, // -y
            15,17,16,

            18,20,19, // +y
            21,23,22,

            24,26,25, // -z
            27,29,28,

            30,32,31, // +z
            33,35,34,
        };

        //unsigned short CubeIndices[36];
        //for (int i = 0; i < 36; ++i)
        //    CubeIndices[i] = i;

        mVertexCount = ARRAYSIZE(CubeVertices);
        mIndexCount = ARRAYSIZE(CubeIndices);

        CD3D11_BUFFER_DESC iDesc(
            sizeof(CubeIndices),
            D3D11_BIND_INDEX_BUFFER
        );

        D3D11_SUBRESOURCE_DATA iData;
        ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
        iData.pSysMem = CubeIndices;
        iData.SysMemPitch = 0;
        iData.SysMemSlicePitch = 0;

        hr = dev->m_pd3dDevice->CreateBuffer(
            &iDesc,
            &iData,
            &mIndexBuffer
        );

        // ------------------------------------------------------------------------------------

        std::shared_ptr<std::vector<D3D11_INPUT_ELEMENT_DESC>> vbdec = std::make_shared<std::vector<D3D11_INPUT_ELEMENT_DESC>>();
        vbdec->resize(3);
        (*vbdec)[0] = DirectX::VertexPositionNormalColor::InputElements[0];
        (*vbdec)[1] = DirectX::VertexPositionNormalColor::InputElements[1];
        (*vbdec)[2] = DirectX::VertexPositionNormalColor::InputElements[2];

        DirectX::ModelMeshPart mesh;
        mesh.indexCount = mIndexCount;
        mesh.startIndex = 0;
        mesh.vertexOffset = 0;
        mesh.vertexStride = sizeof(DirectX::VertexPositionNormalColor);
        mesh.primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        mesh.indexFormat = DXGI_FORMAT_R16_UINT;
        mesh.vbDecl = vbdec;
        mesh.effect = eff;
        mesh.indexBuffer = mIndexBuffer;
        mesh.vertexBuffer = mVertexBuffer;

        ID3D11InputLayout* ilayout;
        mesh.ModifyEffect(dev->m_pd3dDevice, mesh.effect, false);
        mesh.CreateInputLayout(dev->m_pd3dDevice, &be, &ilayout);
        mesh.Draw(dev->m_pd3dDeviceContext, &be, ilayout);
    }
}

