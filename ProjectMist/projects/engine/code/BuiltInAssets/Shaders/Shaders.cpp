#include "Shaders.h"
#include <Graphics/DeviceResources.h>
#include <Graphics/Model/Model.h>
#include <Graphics/RendererComp/RendererComp.h>
#include <EntitySystem/Entity/Entity.h>

#include <d3d11_4.h>

namespace ME
{
    void ColorShader::CreateConstantBuffers(ID3D11Device* dev)
    {
        HRESULT hr = S_OK;

        CD3D11_BUFFER_DESC cbDesc(
            sizeof(ConstantBufferStruct),
            D3D11_BIND_CONSTANT_BUFFER
        );

        hr = dev->CreateBuffer(
            &cbDesc,
            nullptr,
            &m_pConstantBuffer
        );

        DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.7f, 1.5f, 0.f);
        DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, -0.1f, 0.0f, 0.f);
        DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

        DirectX::XMStoreFloat4x4(&mVM.view, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtRH(eye, at, up)));

        float aspectRatio = 16.f / 9.f;

        DirectX::XMStoreFloat4x4(
            &mVM.projection, 
            DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(70), aspectRatio, 0.01f, 100.0f)));
    }

    void ColorShader::Draw(DeviceResources* dev, RendererComp* comp)
    {
        // Use the Direct3D device context to draw.
        ID3D11DeviceContext* context = dev->m_pd3dDeviceContext;

        mVM.world = comp->GetOwner()->mTransform.GetMatrix();
        context->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &mVM, 0, 0);

        // Set up the IA stage by setting the input topology and layout.
        UINT stride = comp->mModel->mVertexLayout->GetVertexSize();
        UINT offset = 0;

        ID3D11Buffer* vertexBuffer = comp->mModel->mVertexLayout->GetVertexBuffer();
        context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        context->IASetIndexBuffer(comp->mModel->mVertexLayout->GetIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        context->IASetInputLayout(mVertexShader->GetInputLayout());

        // Set up the vertex shader stage.
        context->VSSetShader(mVertexShader->GetVertexShader(), nullptr, 0);

        context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

        // Set up the pixel shader stage.
        context->PSSetShader(mPixelShader->GetPixelShader(), nullptr, 0);

        // Calling Draw tells Direct3D to start sending commands to the graphics device.
        context->DrawIndexed(comp->mModel->mVertexLayout->GetIndexCount(), 0, 0);
    }
}