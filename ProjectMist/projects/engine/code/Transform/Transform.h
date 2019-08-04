#pragma once

#include <DirectXMath.h>
#include <Libraries/Math.h>

namespace ME
{
    class Transform3D
    {
    public:
        Transform3D();

        DirectX::XMFLOAT4X4 GetMatrix();

        Vec3 mPosition;
        Vec3 mScale;
        Vec3 mRotation;

    private:
    };
}