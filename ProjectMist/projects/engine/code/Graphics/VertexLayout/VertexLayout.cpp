#include "MistEngine_PCH.h"

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
            {{-0.5, -0.5, +0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, -0.5, +0.5}, {1.0, 1.0, 0.0}},
            {{+0.5, +0.5, +0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, -0.5, +0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, +0.5, +0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, +0.5, +0.5}, {0.0, 0.0, 0.0}},

            {{+0.5, -0.5, +0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, -0.5, -0.5}, {1.0, 1.0, 0.0}},
            {{+0.5, +0.5, -0.5}, {1.0, 0.0, 0.0}},
            {{+0.5, -0.5, +0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, +0.5, -0.5}, {1.0, 0.0, 0.0}},
            {{+0.5, +0.5, +0.5}, {0.0, 0.0, 0.0}},

            {{+0.5, -0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{-0.5, -0.5, -0.5}, {1.0, 1.0, 0.0}},
            {{-0.5, +0.5, -0.5}, {1.0, 0.0, 0.0}},
            {{+0.5, -0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{-0.5, +0.5, -0.5}, {1.0, 0.0, 0.0}},
            {{+0.5, +0.5, -0.5}, {0.0, 0.0, 0.0}},

            {{-0.5, -0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{-0.5, -0.5, +0.5}, {1.0, 1.0, 0.0}},
            {{-0.5, +0.5, +0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, -0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{-0.5, +0.5, +0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, +0.5, -0.5}, {0.0, 0.0, 0.0}},

            {{-0.5, +0.5, +0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, +0.5, +0.5}, {1.0, 1.0, 0.0}},
            {{+0.5, +0.5, -0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, +0.5, +0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, +0.5, -0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, +0.5, -0.5}, {0.0, 0.0, 0.0}},

            {{-0.5, -0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, -0.5, -0.5}, {1.0, 1.0, 0.0}},
            {{+0.5, -0.5, +0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, -0.5, -0.5}, {0.0, 1.0, 0.0}},
            {{+0.5, -0.5, +0.5}, {1.0, 0.0, 0.0}},
            {{-0.5, -0.5, +0.5}, {0.0, 0.0, 0.0}},
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
        unsigned short CubeIndices[36];

        for (int i = 0; i < 12; ++i)
        {
            CubeIndices[i * 3] = i * 3 + 2;
            CubeIndices[i * 3 + 1] = i * 3 + 1;
            CubeIndices[i * 3 + 2] = i * 3;
        }

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





