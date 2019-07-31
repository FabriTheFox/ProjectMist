#pragma once

#include <d3d11_4.h>
#include <DirectXMath.h>
#include <Libraries/Containers.h>

class IVertexLayout
{
public:
    const ME::Vector<D3D11_INPUT_ELEMENT_DESC>& GetInputLayoutDesc() { return mLayout; }
    ID3D11Buffer* GetVertexBuffer() { return mVertexBuffer; }
    ID3D11Buffer* GetIndexBuffer() { return mIndexBuffer; }
    unsigned int GetVertexCount() { return mVertexCount; }
    unsigned int GetIndexCount() { return mIndexCount; }

protected:
    ME::Vector<D3D11_INPUT_ELEMENT_DESC> mLayout;
    ID3D11Buffer* mVertexBuffer = nullptr;
    ID3D11Buffer* mIndexBuffer = nullptr;
    unsigned int mIndexCount = 0;
    unsigned int mVertexCount = 0;
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