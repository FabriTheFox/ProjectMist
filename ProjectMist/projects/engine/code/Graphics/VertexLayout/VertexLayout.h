#pragma once

#include <d3d11_4.h>
#include <DirectXMath.h>
#include <Libraries/Containers.h>

namespace ME
{
    class IVertexLayout
    {
    public:
        const ME::Vector<D3D11_INPUT_ELEMENT_DESC>& GetInputLayoutDesc() const { return mLayout; }
        ID3D11Buffer* GetVertexBuffer() const { return mVertexBuffer; }
        ID3D11Buffer* GetIndexBuffer() const { return mIndexBuffer; }
        unsigned int GetVertexCount() const { return mVertexCount; }
        unsigned int GetIndexCount() const { return mIndexCount; }
        unsigned int GetVertexSize() const { return mVertexSize; }

    protected:
        ME::Vector<D3D11_INPUT_ELEMENT_DESC> mLayout;
        ID3D11Buffer* mVertexBuffer = nullptr;
        ID3D11Buffer* mIndexBuffer = nullptr;
        unsigned int mIndexCount = 0;
        unsigned int mVertexCount = 0;
        unsigned int mVertexSize = 0;
    };

    class VertexLayout : public IVertexLayout
    {
    public:
        struct Vertex
        {
            DirectX::XMFLOAT3 mPosition;
            DirectX::XMFLOAT3 mNormal;
            DirectX::XMFLOAT3 mTextureCoords;
            DirectX::XMFLOAT3 mColor;
        };

    public:
        VertexLayout();
        void Load(ID3D11Device* device, ME::Vector<VertexLayout::Vertex>& vertices);
    };

    class VertexPosColor : public IVertexLayout
    {
    public:
        struct Vertex
        {
            DirectX::XMFLOAT3 mPosition;
            DirectX::XMFLOAT3 mColor;
        };

    public:
        VertexPosColor();
        void Load(ID3D11Device* device, ME::Vector<VertexPosColor::Vertex>& vertices);
    };
}

