#include "InputSystem.h"
#include <Engine/MistEngine.h>

namespace ME
{
    void InputSystem::Initialize()
    {
        ResetInputStatus();
    }

    void InputSystem::Update()
    {
        memcpy_s(&mPreviousKeyStatus.front(), Terminal::VIRTUAL_KEY_COUNT, &mCurrentKeyStatus.front(), Terminal::VIRTUAL_KEY_COUNT);
        memcpy_s(&mPreviousMouseStatus.front(), Terminal::MOUSE_BUTTON_COUNT, &mCurrentMouseStatus.front(), Terminal::MOUSE_BUTTON_COUNT);

        memcpy_s(&mCurrentKeyStatus.front(), Terminal::VIRTUAL_KEY_COUNT, mEngine.Window.mTerminal.mKeyboardKeyStatus, Terminal::VIRTUAL_KEY_COUNT);
        memcpy_s(&mCurrentMouseStatus.front(), Terminal::MOUSE_BUTTON_COUNT, mEngine.Window.mTerminal.mMouseButtonStatus, Terminal::MOUSE_BUTTON_COUNT);

        for (unsigned i = 0; i < Terminal::VIRTUAL_KEY_COUNT; ++i)
        {
            char& current = mCurrentKeyStatus[i];
            char& previous = mPreviousKeyStatus[i];
            
            if (current == Terminal::KEY_DOWN)
            {
                if (previous == KEY_IDLE)
                    current = KEY_TRIGGERED;
                else
                    current = KEY_PRESSED;
            }
            else if (current == Terminal::KEY_UP)
            {
                if (previous == KEY_PRESSED || previous == KEY_TRIGGERED)
                    current = KEY_RELEASED;
                else
                    current = KEY_IDLE;
            }
        }

        for (unsigned i = 0; i < Terminal::MOUSE_BUTTON_COUNT; ++i)
        {
            char& current = mCurrentMouseStatus[i];
            char& previous = mPreviousMouseStatus[i];

            if (current == Terminal::KEY_DOWN)
            {
                if (previous == KEY_IDLE)
                    current = KEY_TRIGGERED;
                else
                    current = KEY_PRESSED;
            }
            else if (current == Terminal::KEY_UP)
            {
                if (previous == KEY_PRESSED || previous == KEY_TRIGGERED)
                    current = KEY_RELEASED;
                else
                    current = KEY_IDLE;
            }
        }
    }

    void InputSystem::Shutdown()
    {
        ResetInputStatus();
    }

    void InputSystem::ResetInputStatus()
    {
        mCurrentKeyStatus.resize(Terminal::VIRTUAL_KEY_COUNT);
        mPreviousKeyStatus.resize(Terminal::VIRTUAL_KEY_COUNT);

        mCurrentMouseStatus.resize(Terminal::MOUSE_BUTTON_COUNT);
        mPreviousMouseStatus.resize(Terminal::MOUSE_BUTTON_COUNT);

        memset(&mCurrentKeyStatus.front(), KEY_IDLE, Terminal::VIRTUAL_KEY_COUNT);
        memset(&mPreviousKeyStatus.front(), KEY_IDLE, Terminal::VIRTUAL_KEY_COUNT);

        memset(&mCurrentMouseStatus.front(), KEY_IDLE, Terminal::MOUSE_BUTTON_COUNT);
        memset(&mPreviousMouseStatus.front(), KEY_IDLE, Terminal::MOUSE_BUTTON_COUNT);
    }
}

