#include "RendererComp.h"

#include <Graphics/DeviceResources.h>
#include <d3dcompiler.h>

#include <Engine/MistEngine.h>
#include <Graphics/Graphics.h>

namespace ME
{
    RTTI_IMPLEMENTATION(RendererComp);

    void RendererComp::OnRegister(MistEngine& engine)
    {
        engine.Graphics.RegisterComponent(this);

        CreateShaders(engine.Graphics.mDeviceResources.m_pd3dDevice);
        CreateBuffers(engine.Graphics.mDeviceResources.m_pd3dDevice);
        CreateViewAndPerspective();
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

    

    void RendererComp::CreateShaders(ID3D11Device* dev)
    {
        
    }

    void RendererComp::CreateBuffers(ID3D11Device* dev)
    {
        
    }

    void RendererComp::OnUpdate()
    {
        //float r0 = DirectX::XMConvertToRadians((float)(m_frameCount % 360));
        //float r1 = DirectX::XMConvertToRadians((float)((m_frameCount * 2) % 360));
        //float r2 = DirectX::XMConvertToRadians((float)((m_frameCount * 4) % 360));
        //
        //// Rotate the cube 1 degree per frame.
        //DirectX::XMStoreFloat4x4(
        //    &m_constantBufferData.world,
        //    DirectX::XMMatrixTranspose(
        //        DirectX::XMMatrixRotationX(r0) *
        //        DirectX::XMMatrixRotationY(r1) *
        //        DirectX::XMMatrixRotationZ(r2)
        //    )
        //);
        //
        //++m_frameCount;
        //
        //if (m_frameCount == MAXUINT)  m_frameCount = 0;
    }

    void RendererComp::Render(DeviceResources* dev)
    {
        // Use the Direct3D device context to draw.
        ID3D11DeviceContext* context = dev->m_pd3dDeviceContext;

        ID3D11RenderTargetView* renderTarget = dev->m_pRenderTarget;
        ID3D11DepthStencilView* depthStencil = dev->m_pDepthStencilView;;

        context->UpdateSubresource(
            m_pConstantBuffer,
            0,
            nullptr,
            &m_constantBufferData,
            0,
            0
        );

        // Clear the render target and the z-buffer.
        const float teal[] = { 0.098f, 0.439f, 0.439f, 1.000f };
        context->ClearRenderTargetView(
            renderTarget,
            teal
        );
        context->ClearDepthStencilView(
            depthStencil,
            D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
            1.0f,
            0);

        // Set the render target.
        context->OMSetRenderTargets(
            1,
            &renderTarget,
            depthStencil
        );

        // Set up the IA stage by setting the input topology and layout.
        UINT stride = sizeof(VertexPositionColor);
        UINT offset = 0;

        context->IASetVertexBuffers(
            0,
            1,
            &m_pVertexBuffer,
            &stride,
            &offset
        );

        context->IASetIndexBuffer(
            m_pIndexBuffer,
            DXGI_FORMAT_R16_UINT,
            0
        );

        context->IASetPrimitiveTopology(
            D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
        );

        context->IASetInputLayout(m_pInputLayout);

        // Set up the vertex shader stage.
        context->VSSetShader(
            m_pVertexShader,
            nullptr,
            0
        );

        context->VSSetConstantBuffers(
            0,
            1,
            &m_pConstantBuffer
        );

        // Set up the pixel shader stage.
        context->PSSetShader(
            m_pPixelShader,
            nullptr,
            0
        );

        // Calling Draw tells Direct3D to start sending commands to the graphics device.
        context->DrawIndexed(
            m_indexCount,
            0,
            0
        );
    }
}

