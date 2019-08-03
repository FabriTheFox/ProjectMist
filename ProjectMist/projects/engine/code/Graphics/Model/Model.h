#pragma once

#include <d3d11_4.h>
#include <DirectXMath.h>

#include <Graphics/VertexLayout/VertexLayout.h>

struct ID3D11Device;

namespace ME
{
    class Model
    {
    public:
        void Create(ID3D11Device* dev);
        IVertexLayout* mVertexLayout = nullptr;
    };
}
