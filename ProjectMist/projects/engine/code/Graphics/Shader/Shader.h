#pragma once

class ID3D11Device;

class Shader
{
public:
    void Create(ID3D11Device* dev);

    struct ConstantBufferStruct{
        DirectX::XMFLOAT4X4 world;
        DirectX::XMFLOAT4X4 view;
        DirectX::XMFLOAT4X4 projection;
    };

    // Assert that the constant buffer remains 16-byte aligned.
    static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

    ID3D11Buffer* m_pConstantBuffer;
    ID3D11VertexShader* m_pVertexShader;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11InputLayout* m_pInputLayoutExtended;
    ID3D11PixelShader* m_pPixelShader;

public:
    void CreateViewAndPerspective();
};