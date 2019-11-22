#pragma once

#include <Engine/MistEngineDefs.h>
#include "Camera.h"

namespace ME
{
    class MistEngine;

    class FreeCamera : public Camera
    {
    public:
        MISTENGINE_DLL FreeCamera(MistEngine* engine = nullptr, const String& name = "");

        MISTENGINE_DLL virtual void OnUpdate() override;

        float mSpeed = 0.01f;
        float mLookSensitivity = 0.01f;
        float mSpeedBoost = 5.f;

    private:
    };
}
