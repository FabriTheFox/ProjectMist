#pragma once

#include <Engine/MistEngineDefs.h>
#include <Engine/System/System.h>
#include <Libraries/Containers.h>
#include <Libraries/Math.h>

namespace ME
{
    class WindowEvent;

    class MISTENGINE_DLL InputSystem : public System
    {
        SYSTEM_DECLARATION(InputSystem);
    public:

        void Initialize() override final;
        void Update() override final;
        void Shutdown() override final;

        static const char KEY_IDLE = 0;
        static const char KEY_PRESSED = 1;
        static const char KEY_TRIGGERED = 2;
        static const char KEY_RELEASED = 3;

        IVec2 GetMouseMovement() const { return { mCurrentMousePos[0] - mPreviousMousePos[0], mCurrentMousePos[1] - mPreviousMousePos[1] }; }
        IVec2 GetMousePosition() const { return { mCurrentMousePos[0], mCurrentMousePos[1] }; }

        bool IsKeyIdle(unsigned key) const { return key < mCurrentKeyStatus.size() && mCurrentKeyStatus[key] == KEY_IDLE; }
        bool IsKeyPressed(unsigned key) const {return key < mCurrentKeyStatus.size() && mCurrentKeyStatus[key] == KEY_PRESSED;}
        bool IsKeyTriggered(unsigned key) const { return key < mCurrentKeyStatus.size() && mCurrentKeyStatus[key] == KEY_TRIGGERED; }
        bool IsKeyReleased(unsigned key) const { return key < mCurrentKeyStatus.size() && mCurrentKeyStatus[key] == KEY_RELEASED; }

        bool IsMouseButtonIdle(unsigned button) const { return button < mCurrentMouseStatus.size() && mCurrentMouseStatus[button] == KEY_IDLE; }
        bool IsMouseButtonPressed(unsigned button) const { return button < mCurrentMouseStatus.size() && mCurrentMouseStatus[button] == KEY_PRESSED; }
        bool IsMouseButtonTriggered(unsigned button) const { return button < mCurrentMouseStatus.size() && mCurrentMouseStatus[button] == KEY_TRIGGERED; }
        bool IsMouseButtonReleased(unsigned button) const { return button < mCurrentMouseStatus.size() && mCurrentMouseStatus[button] == KEY_RELEASED; }

    private:
        void ResetInputStatus();

        // Events
        void OnWindowEvent(const WindowEvent& ev);

        bool mNeedsReset = false;

        std::vector<char>mPreviousKeyStatus;
        std::vector<char>mCurrentKeyStatus;

        std::vector<char>mCurrentMouseStatus;
        std::vector<char>mPreviousMouseStatus;

        int mCurrentMousePos[2];
        int mPreviousMousePos[2];
    };
}