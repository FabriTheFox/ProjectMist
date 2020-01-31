#include "MistEngine_PCH.h"

#include "Texture.h"
#include <wincodec.h>
#include <Utilities/StringUtils.h>

namespace ME
{
    RTTI_IMPLEMENTATION(Texture);

    void Texture::LoadToGraphicsDevice(ID3D11Device* device)
    {
        // Create sampler.
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        HRESULT res = device->CreateSamplerState(&samplerDesc, &mSamplerState);

        // Create texture.
        D3D11_TEXTURE2D_DESC txtDesc = {};
        txtDesc.MipLevels = txtDesc.ArraySize = 1;
        txtDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB; // sunset.jpg is in sRGB colorspace
        txtDesc.SampleDesc.Count = 1;
        txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
        txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        txtDesc.Width = mWidth;
        txtDesc.Height = mHeight;

        D3D11_SUBRESOURCE_DATA initialData = {};

        initialData.pSysMem = mTextureData.data();
        initialData.SysMemPitch = txtDesc.Width * sizeof(uint32_t);

        ID3D11Texture2D* tex;
        res = device->CreateTexture2D(&txtDesc, &initialData, &tex);
        res = device->CreateShaderResourceView(tex, nullptr, &mTexture);

        mLoadedToGraphicsDevice = true;
    }
}


