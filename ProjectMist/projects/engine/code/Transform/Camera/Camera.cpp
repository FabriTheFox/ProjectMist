#include <Transform/Camera/Camera.h>

namespace ME
{
    RTTI_IMPLEMENTATION(Camera);

    Camera::Camera(MistEngine* engine /*= nullptr*/, const String& name /*= ""*/)
        : Entity(engine, name)
    {
    }

    void Camera::UpdateMatrices()
    {
        DirectX::XMStoreFloat4x4(&mCameraMatrix, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtRH(mEyePosition, mTargetPosition, mUpVector)));

        DirectX::XMStoreFloat4x4(
            &mProjectionMatrix,
            DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(mFOV_V), mAspectRatio, mNearPlane, mFarPlane)));
    }

    Mat4 Camera::GetViewMatrix() const
    {
        return mCameraMatrix;
    }

    Mat4 Camera::GetProjectionMatrix() const
    {
        return mProjectionMatrix;
    }

    Vec4 Camera::GetViewDirectionNormalized() const
    {
        return DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(mTargetPosition, mEyePosition));
    }
}

