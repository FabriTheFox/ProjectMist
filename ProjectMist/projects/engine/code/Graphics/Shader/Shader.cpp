#include "Shader.h"

#include <d3d11_4.h>
#include <DirectXMath.h>

#include <Graphics/DeviceResources.h>
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

#include <Graphics/VertexLayout/VertexLayout.h>
namespace ME
{
    void VertexShader::Create(ID3D11Device* dev, const ME::String& file, const IVertexLayout* ilay)
    {
        HRESULT hr = S_OK;

        // Compile the vertex shader
        ID3DBlob* pVSBlob = nullptr;
        hr = CompileShaderFromFile(L"shaders/CubeVertexShader.hlsl", "VS", "vs_4_0", &pVSBlob);
        if (FAILED(hr))
        {
            return;
        }

        // Create the vertex shader
        hr = dev->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVertexShader);
        if (FAILED(hr))
        {
            pVSBlob->Release();
            return;
        }

        const auto& ilaydesc = ilay->GetInputLayoutDesc();

        // Create the input layout
        hr = dev->CreateInputLayout(ilaydesc.data(), ilaydesc.size(), pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pInputLayout);
        pVSBlob->Release();
        if (FAILED(hr))
            return;
    }

    void PixelShader::Create(ID3D11Device* dev, const ME::String& file)
    {
        HRESULT hr = S_OK;

        // Compile the pixel shader
        ID3DBlob* pPSBlob = nullptr;
        hr = CompileShaderFromFile(L"shaders/CubePixelShader.hlsl", "PS", "ps_4_0", &pPSBlob);
        if (FAILED(hr))
        {
            return;
        }

        // Create the pixel shader
        hr = dev->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPixelShader);
        pPSBlob->Release();
        if (FAILED(hr))
            return;
    }
}

