#include "MistEngine_PCH.h"

#include "Transform.h"

#include <d3d11_4.h>

namespace ME
{
    Transform3D::Transform3D()
        : mPosition(0, 0, 0)
        , mRotation(0, 0, 0)
        , mScale(1, 1, 1)
    {
    }

    Mat4 Transform3D::GetMatrix()
    {
        Mat4 matrix;

        DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixTranspose(
              DirectX::XMMatrixScaling(mScale.x, mScale.y, mScale.z)
            * DirectX::XMMatrixRotationX(mRotation.x) 
            * DirectX::XMMatrixRotationY(mRotation.y) 
            * DirectX::XMMatrixRotationZ(mRotation.z)
            * DirectX::XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z)));

        return matrix;
    }
}