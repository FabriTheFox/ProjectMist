#pragma once

#include <Engine/MistEngineDefs.h>
#include <Engine/System/System.h>
#include <Graphics/Graphics.h>
#include <RTTI/RTTI.h>

#include <Windows.h>
#include <Windowsx.h>

namespace ME
{
    constexpr unsigned VK_Count = 0xFE;

    class MISTENGINE_DLL Terminal
    {
        friend class Window;
    public:
        Terminal();
        ~Terminal();

        bool IsKeyDown(unsigned key);
        bool IsKeyUp(unsigned key);

    private:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        static char mKeyboardPrevious[VK_Count];
        static char mKeyboardCurrent[VK_Count];
    };
}
