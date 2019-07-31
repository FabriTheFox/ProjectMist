#include "Model.h"

void Model::Create(ID3D11Device* dev)
{
    auto vert = new VertexPosColor();

    ME::Vector<VertexPosColor::Vertex> vertices;
    vert->Load(dev, vertices);
    mVertexLayout = vert;
}