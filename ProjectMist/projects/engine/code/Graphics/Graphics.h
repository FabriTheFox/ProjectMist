#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>
#include <Engine/Singleton.h>
#include <RTTI/RTTI.h>

#include <d3d11_4.h>
#include <DirectXMath.h>

struct ID3D11Device;

namespace ME
{
    class Graphics
    {
        RTTI_DECLARATION(Graphics);
        SINGLETON_DEFCTOR_DLL(Graphics, MISTENGINE_DLL);
    public:

        void Initialize();
        void Update();
        void Render(ID3D11DeviceContext* devcontext, ID3D11RenderTargetView* rt, ID3D11DepthStencilView* ds);

        void CreateShaders(ID3D11Device* dev);
        void CreateBuffers(ID3D11Device* dev);
        void CreateViewAndPerspective();

    //private:
        typedef struct _constantBufferStruct {
            DirectX::XMFLOAT4X4 world;
            DirectX::XMFLOAT4X4 view;
            DirectX::XMFLOAT4X4 projection;
        } ConstantBufferStruct;

        // Assert that the constant buffer remains 16-byte aligned.
        static_assert((sizeof(ConstantBufferStruct) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

        //-----------------------------------------------------------------------------
        // Per-vertex data
        //-----------------------------------------------------------------------------
        typedef struct _vertexPositionColor
        {
            DirectX::XMFLOAT3 pos;
            DirectX::XMFLOAT3 color;
        } VertexPositionColor;

        typedef struct _vertexPositionColorTangent
        {
            DirectX::XMFLOAT3 pos;
            DirectX::XMFLOAT3 normal;
            DirectX::XMFLOAT3 tangent;
        } VertexPositionColorTangent;

        ConstantBufferStruct m_constantBufferData;
        unsigned int  m_indexCount;
        unsigned int  m_frameCount;

        ID3D11Buffer* m_pVertexBuffer;
        ID3D11Buffer* m_pIndexBuffer;
        ID3D11VertexShader* m_pVertexShader;
        ID3D11InputLayout* m_pInputLayout;
        ID3D11InputLayout* m_pInputLayoutExtended;
        ID3D11PixelShader* m_pPixelShader;
        ID3D11Buffer* m_pConstantBuffer;
    };
}
