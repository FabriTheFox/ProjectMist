#pragma once

#include <Transform/Transform.h>
#include <EntitySystem/Entity/Entity.h>

namespace ME
{
    class Camera
    {
    public:
        void UpdateMatrices();
        Mat4 GetViewMatrix();
        Mat4 GetProjectionMatrix();

    private:
        Mat4 mCameraMatrix;
        Mat4 mProjectionMatrix;
        Mat4 mCameraProjectionMatrix;

        float mAspectRatio{ 16.f / 9.f };
        float mNearPlane{ 0.1f };
        float mFarPlane{ 500.f };
        float mFOV_V{ 45.f };
        float mFocalDistance{ 3.f };
    };
}