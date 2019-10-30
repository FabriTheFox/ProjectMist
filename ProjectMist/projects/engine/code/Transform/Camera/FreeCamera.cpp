#include "FreeCamera.h"
#include <InputSystem/InputSystem.h>
#include <InputSystem/InputKeyCodes.h>

namespace ME
{
    void FreeCamera::Update()
    {
    }

    void FreeCamera::HandleInput(const InputSystem& inputsystem)
    {
        using namespace DirectX;

        Vec4 dir = GetViewDirectionNormalized();
        Vec4 rightvec = XMVector3Normalize(XMVector3Cross(dir, mUpVector));

        if (inputsystem.IsMouseButtonPressed(0))
        {
            IVec2 mousemove = inputsystem.GetMouseMovement();
            dir = XMVector3Rotate(dir, XMQuaternionRotationNormal(rightvec, -mousemove.y * 0.01f));
            dir = XMVector3Rotate(dir, XMQuaternionRotationAxis(mUpVector, -mousemove.x * 0.01f));
            rightvec = XMVector3Normalize(XMVector3Cross(mUpVector, dir));
        }        

        if (inputsystem.IsKeyPressed(VK_RIGHT) || inputsystem.IsKeyPressed('D'))
        {
            mEyePosition += rightvec * mSpeed;
        }
        if (inputsystem.IsKeyPressed(VK_LEFT) || inputsystem.IsKeyPressed('A'))
        {
            mEyePosition += -rightvec * mSpeed;
        }
        if (inputsystem.IsKeyPressed(VK_UP) || inputsystem.IsKeyPressed('W'))
        {
            mEyePosition += dir * mSpeed;
        }
        if (inputsystem.IsKeyPressed(VK_DOWN) || inputsystem.IsKeyPressed('S'))
        {
            mEyePosition += -dir * mSpeed;
        }

        if (inputsystem.IsKeyPressed(VK_SPACE))
        {
            if (inputsystem.IsKeyPressed(VK_SHIFT))
            {
                mEyePosition += -mUpVector * mSpeed;
            }
            else
            {
                mEyePosition += mUpVector * mSpeed;
            }
        }

        mTargetPosition = mEyePosition + dir;
    }
}