#pragma once

#include <Libraries/Containers.h>
class ID3D11Device;

class ShaderProgram
{
public:
    void Create(ID3D11Device* dev);
    
    virtual void CreateConstantBuffers() = 0;
    virtual void Draw() = 0;

    struct ConstantBufferStruct{
        DirectX::XMFLOAT4X4 world;
        DirectX::XMFLOAT4X4 view;
        DirectX::XMFLOAT4X4 projection;
    };
    static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

    ME::Vector<ID3D11Buffer*> mConstantBuffers;
    ID3D11Buffer* m_pConstantBuffer = nullptr;

public:
    void CreateViewAndPerspective();
};

class IVertexLayout;
class VertexShader
{
public:
    void Create(ID3D11Device* dev, const ME::String& file, const IVertexLayout* verlay);

private:
    ID3D11VertexShader* m_pVertexShader = nullptr;
    ID3D11InputLayout* m_pInputLayout = nullptr;
    ID3D11InputLayout* m_pInputLayoutExtended = nullptr;
};

class PixelShader
{
public:
    void Create(ID3D11Device* dev, const ME::String& file);

private:
    ID3D11PixelShader * m_pPixelShader = nullptr;
};