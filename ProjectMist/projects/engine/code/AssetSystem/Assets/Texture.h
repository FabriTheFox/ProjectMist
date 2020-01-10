#pragma once

#include <d3d11_4.h>
#include <vector>

namespace ME
{
    class Texture
    {
    public:
        //bool Initialize(ID3D11Device*, WCHAR*);
        //ID3D11ShaderResourceView* GetTexture();

        std::vector<uint8_t> LoadBGRAImage(const wchar_t* filename, uint32_t& width, uint32_t& height);

    //private:

        ID3D11ShaderResourceView* m_texture;
    };
}