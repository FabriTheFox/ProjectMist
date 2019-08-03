#include "VertexLayout.h"

namespace ME
{
    VertexLayout::VertexLayout()
    {
        mLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };
    }

    void VertexLayout::Load(ID3D11Device* device, ME::Vector<Vertex>& vertices)
    {
        (void)(device);
        (void)(vertices);
    }

    // ====================================================================================================================

    VertexPosColor::VertexPosColor()
    {
        mLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        mVertexSize = sizeof(VertexPosColor::Vertex);
    }

    void VertexPosColor::Load(ID3D11Device* device, ME::Vector<VertexPosColor::Vertex>& vertices)
    {
        HRESULT hr = S_OK;

        // Create cube geometry.
        VertexPosColor::Vertex CubeVertices[] =
        {
            { DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0,   0,   0), },
        { DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0,   0,   1), },
        { DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0,   1,   0), },
        { DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0,   1,   1), },

        { DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(1,   0,   0), },
        { DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(1,   0,   1), },
        { DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(1,   1,   0), },
        { DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1,   1,   1), },
        };

        // Create vertex buffer:

        CD3D11_BUFFER_DESC vDesc(
            sizeof(CubeVertices),
            D3D11_BIND_VERTEX_BUFFER
        );

        D3D11_SUBRESOURCE_DATA vData;
        ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
        vData.pSysMem = CubeVertices;
        vData.SysMemPitch = 0;
        vData.SysMemSlicePitch = 0;

        hr = device->CreateBuffer(
            &vDesc,
            &vData,
            &mVertexBuffer
        );

        // Create index buffer:
        unsigned short CubeIndices[] =
        {
            0,2,1, // -x
            1,2,3,

            4,5,6, // +x
            5,7,6,

            0,1,5, // -y
            0,5,4,

            2,6,7, // +y
            2,7,3,

            0,4,6, // -z
            0,6,2,

            1,3,7, // +z
            1,7,5,
        };

        mVertexCount = ARRAYSIZE(CubeVertices);
        mIndexCount = ARRAYSIZE(CubeIndices);

        CD3D11_BUFFER_DESC iDesc(
            sizeof(CubeIndices),
            D3D11_BIND_INDEX_BUFFER
        );

        D3D11_SUBRESOURCE_DATA iData;
        ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
        iData.pSysMem = CubeIndices;
        iData.SysMemPitch = 0;
        iData.SysMemSlicePitch = 0;

        hr = device->CreateBuffer(
            &iDesc,
            &iData,
            &mIndexBuffer
        );
    }
}





