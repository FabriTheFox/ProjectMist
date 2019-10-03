#include <Transform/Camera/Camera.h>

namespace ME
{
    void Camera::UpdateMatrices()
    {
        DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.7f, 1.5f, 0.f);
        DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, -0.1f, 0.0f, 0.f);
        DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

        DirectX::XMStoreFloat4x4(&mCameraMatrix, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtRH(eye, at, up)));

        DirectX::XMStoreFloat4x4(
            &mProjectionMatrix,
            DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(mFOV_V), mAspectRatio, mNearPlane, mFarPlane)));
    }

    Mat4 Camera::GetViewMatrix()
    {
        return mCameraMatrix;
    }

    Mat4 Camera::GetProjectionMatrix()
    {
        return mProjectionMatrix;
    }
}

