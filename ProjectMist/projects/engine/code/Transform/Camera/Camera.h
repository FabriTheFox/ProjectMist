#pragma once

#include <Transform/Transform.h>
#include <EntitySystem/Entity/Entity.h>

namespace ME
{
    class InputSystem;
    class MistEngine;

    class Camera : public Entity
    {
        RTTI_DECLARATION(Camera);
        NON_COPYABLE(Camera);

    public:
        Camera(MistEngine* engine = nullptr, const String& name = "");

        //virtual void OnUpdate() override {}

        void UpdateMatrices();
        Mat4 GetViewMatrix() const;
        Mat4 GetProjectionMatrix() const;

        Vec4 GetViewDirectionNormalized() const;

        Vec4 mEyePosition{ 0.0f, 0.0f, 5.0f };
        Vec4 mTargetPosition{ 0.0f, 0.0f, 0.0f };
        Vec4 mUpVector{ 0.0f, 1.0f, 0.0f };

        float mAspectRatio = 16.f / 9.f;
        float mNearPlane = 0.1f;
        float mFarPlane = 500.f;
        float mFOV_V = 45.f;
        float mFocalDistance = 3.f;

    private:
        Mat4 mCameraMatrix;
        Mat4 mProjectionMatrix;
        Mat4 mCameraProjectionMatrix; 
    };
}