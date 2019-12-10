#include "MistEngine_PCH.h"

#include "Model.h"

namespace ME
{
    void Model::Create(ID3D11Device* dev)
    {
        auto vert = new VertexPosColor();

        ME::Vector<VertexPosColor::Vertex> vertices;
        vert->Load(dev, vertices);
        mVertexLayout = vert;
    }
}