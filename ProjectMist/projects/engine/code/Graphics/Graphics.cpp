#include "Graphics.h"

#include <Windows.h>


#include <Graphics/DeviceResources.h>

namespace ME
{
    RTTI_IMPLEMENTATION(Graphics);

    void Graphics::Initialize()
    {
    }

    #include <d3dcompiler.h>
    HRESULT CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
    {
        HRESULT hr = S_OK;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // Disable optimizations to further improve shader debugging
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

        ID3DBlob* pErrorBlob = nullptr;
        hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
            dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
        if (FAILED(hr))
        {
            if (pErrorBlob)
            {
                OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
                pErrorBlob->Release();
            }
            return hr;
        }
        if (pErrorBlob) pErrorBlob->Release();

        return S_OK;
    }

    void Graphics::CreateShaders(ID3D11Device* dev)
    {
        HRESULT hr = S_OK;

        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        hr = CompileShaderFromFile(L"CubeVertexShader.hlsl", "VS", "vs_4_0", &pVSBlob);
        if (FAILED(hr))
        {
            return ;
        }

        // Create the vertex shader
        hr = dev->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVertexShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return;
        }

        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = ARRAYSIZE(layout);

        // Create the input layout
        hr = dev->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
            pVSBlob->GetBufferSize(), &m_pInputLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return;

        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        hr = CompileShaderFromFile(L"CubePixelShader.hlsl", "PS", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            return ;
        }

        // Create the pixel shader
        hr = dev->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return ;

        CD3D11_BUFFER_DESC cbDesc(
            sizeof(ConstantBufferStruct),
            D3D11_BIND_CONSTANT_BUFFER
        );

        hr = dev->CreateBuffer(
            &cbDesc,
            nullptr,
            &m_pConstantBuffer
        );
    }

    void Graphics::CreateBuffers(ID3D11Device* dev)
    {
        HRESULT hr = S_OK;

        // Use the Direct3D device to load resources into graphics memory.
        ID3D11Device* device = dev;

        // Create cube geometry.
        VertexPositionColor CubeVertices[] =
        {
        { DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0,   0,   0), },
        { DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0,   0,   1), },
        { DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0,   1,   0), },
        { DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0,   1,   1), },

        { DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(1,   0,   0), },
        { DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(1,   0,   1), },
        { DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(1,   1,   0), },
        { DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1,   1,   1), },
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

        hr = device->CreateBuffer(
            &vDesc,
            &vData,
            &m_pVertexBuffer
        );

        // Create index buffer:
        unsigned short CubeIndices[] =
        {
            0,2,1, // -x
            1,2,3,

            4,5,6, // +x
            5,7,6,

            0,1,5, // -y
            0,5,4,

            2,6,7, // +y
            2,7,3,

            0,4,6, // -z
            0,6,2,

            1,3,7, // +z
            1,7,5,
        };

        m_indexCount = ARRAYSIZE(CubeIndices);

        CD3D11_BUFFER_DESC iDesc(
            sizeof(CubeIndices),
            D3D11_BIND_INDEX_BUFFER
        );

        D3D11_SUBRESOURCE_DATA iData;
        ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
        iData.pSysMem = CubeIndices;
        iData.SysMemPitch = 0;
        iData.SysMemSlicePitch = 0;

        hr = device->CreateBuffer(
            &iDesc,
            &iData,
            &m_pIndexBuffer
        );
    }

    void Graphics::CreateViewAndPerspective()
    {
        DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.7f, 1.5f, 0.f);
        DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, -0.1f, 0.0f, 0.f);
        DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

        DirectX::XMStoreFloat4x4(
            &m_constantBufferData.view,
            DirectX::XMMatrixTranspose(
                DirectX::XMMatrixLookAtRH(
                    eye,
                    at,
                    up
                )
            )
        );

        float aspectRatio = 16.f/9.f;

        DirectX::XMStoreFloat4x4(
            &m_constantBufferData.projection,
            DirectX::XMMatrixTranspose(
                DirectX::XMMatrixPerspectiveFovRH(
                    DirectX::XMConvertToRadians(70),
                    aspectRatio,
                    0.01f,
                    100.0f
                )
            )
        );
    }

    void Graphics::Update()
    {
        // Rotate the cube 1 degree per frame.
        DirectX::XMStoreFloat4x4(
            &m_constantBufferData.world,
            DirectX::XMMatrixTranspose(
                DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians((float)m_frameCount++) * 0.5f) * 
                DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians((float)m_frameCount++)) *
                DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians((float)m_frameCount++) * 0.25f)
            )
        );

        if (m_frameCount == MAXUINT)  m_frameCount = 0;
    }

    void Graphics::Render(ID3D11DeviceContext* devcontext, ID3D11RenderTargetView* rt, ID3D11DepthStencilView* ds)
    {
        // Use the Direct3D device context to draw.
        ID3D11DeviceContext* context = devcontext;

        ID3D11RenderTargetView* renderTarget = rt;
        ID3D11DepthStencilView* depthStencil = ds;

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