#pragma once

#include <DirectXMath.h>
#include <Libraries/Math.h>

namespace ME
{
    class Transform3D
    {
    public:
        Transform3D();

        Mat4 GetMatrix();

        FVec3 mPosition;
        FVec3 mScale;
        FVec3 mRotation;

    private:
    };
}