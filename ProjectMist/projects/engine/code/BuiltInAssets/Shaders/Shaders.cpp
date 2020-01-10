#include "MistEngine_PCH.h"

#include "Shaders.h"
#include <Graphics/DeviceResources.h>
#include <Graphics/Model/Model.h>
#include <Graphics/RendererComp/RendererComp.h>
#include <EntitySystem/Entity/Entity.h>
#include <Transform/Camera/Camera.h>

#include <d3d11_4.h>

namespace ME
{
    void ColorShader::CreateConstantBuffers(ID3D11Device* dev)
    {
        HRESULT hr = S_OK;
        CD3D11_BUFFER_DESC cbDesc(sizeof(ConstantBufferStruct), D3D11_BIND_CONSTANT_BUFFER);
        hr = dev->CreateBuffer(&cbDesc, nullptr, &m_pConstantBuffer);
    }

    void ColorShader::Draw(DeviceResources* dev, RendererComp* comp)
    {
        // Use the Direct3D device context to draw.
        ID3D11DeviceContext* context = dev->m_pd3dDeviceContext;

        mConstantBuffer.world = comp->GetOwner()->mTransform.GetMatrix();
        mConstantBuffer.view = comp->mCamera->GetViewMatrix();
        mConstantBuffer.projection = comp->mCamera->GetProjectionMatrix();

        context->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &mConstantBuffer, 0, 0);

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

        // Set texture and sampler.
        auto sampler = dev->mCoolSampler;
        context->PSSetSamplers(0, 1, &sampler);

        auto texture = dev->mCoolTexture;
        context->PSSetShaderResources(0, 1, &texture);

        // Calling Draw tells Direct3D to start sending commands to the graphics device.
        context->DrawIndexed(comp->mModel->mVertexLayout->GetIndexCount(), 0, 0);
    }

    // ------------------------------------------------------------------------------------------
    void TextureShader::CreateConstantBuffers(ID3D11Device* dev)
    {
        HRESULT hr = S_OK;
        CD3D11_BUFFER_DESC cbDesc(sizeof(ConstantBufferStruct), D3D11_BIND_CONSTANT_BUFFER);
        hr = dev->CreateBuffer(&cbDesc, nullptr, &m_pConstantBuffer);
    }

    void TextureShader::Draw(DeviceResources* dev, RendererComp* comp)
    {
        // Use the Direct3D device context to draw.
        ID3D11DeviceContext* context = dev->m_pd3dDeviceContext;

        mConstantBuffer.world = comp->GetOwner()->mTransform.GetMatrix();
        mConstantBuffer.view = comp->mCamera->GetViewMatrix();
        mConstantBuffer.projection = comp->mCamera->GetProjectionMatrix();

        context->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &mConstantBuffer, 0, 0);

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

        // Set texture and sampler.
        auto sampler = dev->mCoolSampler;
        context->PSSetSamplers(0, 1, &sampler);

        auto texture = dev->mCoolTexture;
        context->PSSetShaderResources(0, 1, &texture);

        // Calling Draw tells Direct3D to start sending commands to the graphics device.
        context->DrawIndexed(comp->mModel->mVertexLayout->GetIndexCount(), 0, 0);
    }
}