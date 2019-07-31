#pragma once

#include <d3d11_4.h>
#include <DirectXMath.h>

#include <Graphics/InputLayout/VertexLayout.h>

class ID3D11Device;

class Model
{
public:
    void Create(ID3D11Device* dev);
    IVertexLayout* mVertexLayout = nullptr;
};