#pragma once

#include <Graphics/Shader/Shader.h>
#include <DirectXMath.h>

struct ID3D11Device;

namespace ME
{
    struct StandardTransform
    {
        DirectX::XMFLOAT4X4 world;
        DirectX::XMFLOAT4X4 view;
        DirectX::XMFLOAT4X4 projection;
    };

    class MISTENGINE_DLL ColorShader : public ShaderProgram
    {
    public:
        void CreateConstantBuffers(ID3D11Device* dev) override final;
        void Draw(DeviceResources* dev, RendererComp* comp) override final;

    public:
        struct ConstantBufferStruct 
            : public StandardTransform
        {
        };
        static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

        ConstantBufferStruct mConstantBuffer;
    };

    class MISTENGINE_DLL TextureShader : public ShaderProgram
    {
    public:
        void CreateConstantBuffers(ID3D11Device* dev) override final;
        void Draw(DeviceResources* dev, RendererComp* comp) override final;

    public:
        struct ConstantBufferStruct 
            : public StandardTransform
        {
        };
        static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

        ConstantBufferStruct mConstantBuffer;
    };
}