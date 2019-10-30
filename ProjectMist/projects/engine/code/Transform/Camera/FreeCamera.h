#pragma once

#include <Engine/MistEngineDefs.h>
#include "Camera.h"

namespace ME
{
    class FreeCamera : public Camera
    {
    public:
        MISTENGINE_DLL virtual void Update() override;
        MISTENGINE_DLL virtual void HandleInput(const InputSystem& inputsystem) override;

        float mSpeed = 0.01f;

    private:
    };
}
