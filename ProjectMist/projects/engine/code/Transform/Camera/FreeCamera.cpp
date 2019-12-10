#include "MistEngine_PCH.h"

#include "FreeCamera.h"
#include <InputSystem/InputSystem.h>
#include <EntitySystem/EntitySystem.h>
#include <InputSystem/InputKeyCodes.h>
#include <Engine/MistEngine.h>
#include <iostream>
#include "EntitySystem/Entity/Entity.h"

namespace ME
{
    FreeCamera::FreeCamera(MistEngine* engine /*= nullptr*/, const String& name /*= ""*/)
        : Camera(engine, name)
    {
    }

    void FreeCamera::OnUpdate()
    {
        using namespace DirectX;
        InputSystem& inputsystem = mEngine->InputSystem;

        Vec4 dir = GetViewDirectionNormalized();
        Vec4 rightvec = XMVector3Normalize(XMVector3Cross(dir, mUpVector));

        float speed = mSpeed;

        if (inputsystem.IsKeyPressed(VK_SHIFT))
        {
            speed *= mSpeedBoost;
        }

        if (inputsystem.IsMouseButtonPressed(InputSystem::MOUSE_BUTTON_RIGHT))
        {
            IVec2 mousemove = inputsystem.GetMouseMovement();

            // Rotate around right axis (vertical movement)
            dir = XMVector3Rotate(dir, XMQuaternionRotationNormal(rightvec, -mousemove.y * mLookSensitivity));
            // Rotate around up axis (horizontal movement)
            dir = XMVector3Rotate(dir, XMQuaternionRotationNormal(mUpVector, -mousemove.x * mLookSensitivity));
            rightvec = XMVector3Normalize(XMVector3Cross(dir, mUpVector));
        }        

        if (inputsystem.IsKeyPressed(VK_RIGHT) || inputsystem.IsKeyPressed('D'))
        {
            mEyePosition += rightvec * speed;
        }
        if (inputsystem.IsKeyPressed(VK_LEFT) || inputsystem.IsKeyPressed('A'))
        {
            mEyePosition += -rightvec * speed;
        }
        if (inputsystem.IsKeyPressed(VK_UP) || inputsystem.IsKeyPressed('W'))
        {
            mEyePosition += dir * speed;
        }
        if (inputsystem.IsKeyPressed(VK_DOWN) || inputsystem.IsKeyPressed('S'))
        {
            mEyePosition += -dir * speed;
        }

        if (inputsystem.IsKeyPressed(VK_SPACE))
        {
            if (inputsystem.IsKeyPressed(VK_CONTROL))
            {
                mEyePosition += -mUpVector * speed;
            }
            else
            {
                mEyePosition += mUpVector * speed;
            }
        }

        mTargetPosition = mEyePosition + dir;
    }
}