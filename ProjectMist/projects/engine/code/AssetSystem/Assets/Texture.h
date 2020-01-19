#pragma once

#include <d3d11_4.h>
#include <vector>
#include <AssetSystem/AssetSystem.h>

namespace ME
{
    class MISTENGINE_DLL Texture : public Asset
    {
        RTTI_DECLARATION(Texture);
         

    public:
        void Load(const String& path) override;
        void LoadBGRAImage(const String& path);

        void LoadToGraphicsDevice(ID3D11Device* device);

    //private:

        bool mLoadedToGraphicsDevice = false;

        unsigned mWidth = 0;
        unsigned mHeight = 0;

        std::vector<uint8_t> mTextureData;
        ID3D11SamplerState* mSamplerState = nullptr;
        ID3D11ShaderResourceView* mTexture = nullptr;
    };
}