#pragma once

#include <Engine/MistEngineDefs.h>
#include <Engine/System/System.h>
#include <Graphics/Graphics.h>
#include <RTTI/RTTI.h>

#include <Windows.h>
#include <WinUser.h>

namespace ME
{
    class MISTENGINE_DLL Terminal
    {
        friend class Window;
    public:
        Terminal();
        ~Terminal();

        bool IsKeyDown(unsigned key) const;
        bool IsKeyUp(unsigned key) const;

        bool IsMouseButtonDown(unsigned button) const;
        bool IsMouseButtonUp(unsigned button) const;

        static const unsigned VIRTUAL_KEY_COUNT = 0xFE;
        static const unsigned MOUSE_BUTTON_COUNT = 3u;

        static const char KEY_UP = 0;
        static const char KEY_DOWN = 1;

        static char mKeyboardKeyStatus[VIRTUAL_KEY_COUNT];
        static char mMouseButtonStatus[MOUSE_BUTTON_COUNT];

    private:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
}
