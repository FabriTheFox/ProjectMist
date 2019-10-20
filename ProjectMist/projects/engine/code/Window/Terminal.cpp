#include "Terminal.h"

#include <iostream>

// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ME
{
    char Terminal::mKeyboardKeyStatus[VIRTUAL_KEY_COUNT];
    char Terminal::mMouseButtonStatus[MOUSE_BUTTON_COUNT];

    Terminal::Terminal()
    {
        memset(mKeyboardKeyStatus, 0, VIRTUAL_KEY_COUNT);
        memset(mMouseButtonStatus, 0, MOUSE_BUTTON_COUNT);
    }

    Terminal::~Terminal()
    {
    }

    bool Terminal::IsKeyDown(unsigned key) const
    {
        return key < VIRTUAL_KEY_COUNT && mKeyboardKeyStatus[key] == 1;
    }

    bool Terminal::IsKeyUp(unsigned key) const
    {
        return key < VIRTUAL_KEY_COUNT && mKeyboardKeyStatus[key] == 0;
    }

    bool Terminal::IsMouseButtonDown(unsigned button) const
    {
        return button < MOUSE_BUTTON_COUNT && mMouseButtonStatus[button] == 1;
    }

    bool Terminal::IsMouseButtonUp(unsigned button) const
    {
        return button < MOUSE_BUTTON_COUNT && mMouseButtonStatus[button] == 0;
    }

    LRESULT CALLBACK Terminal::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
            return true;

        switch (uMsg)
        {
        case WM_KEYDOWN:
        {
            if (wParam >= 0 && wParam < VIRTUAL_KEY_COUNT)
            {
                mKeyboardKeyStatus[wParam] = KEY_DOWN;
            }
            break;
        }

        case WM_KEYUP:
        {
            if (wParam >= 0 && wParam < VIRTUAL_KEY_COUNT)
            {
                mKeyboardKeyStatus[wParam] = KEY_UP;
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {
            mMouseButtonStatus[0] = KEY_DOWN;
            break;
            //int xPos = GET_X_LPARAM(lParam);
            //int yPos = GET_Y_LPARAM(lParam);
        }
        case WM_RBUTTONDOWN:
        {
            mMouseButtonStatus[1] = KEY_DOWN;
            break;
        }
        case WM_MBUTTONDOWN:
        {
            mMouseButtonStatus[2] = KEY_DOWN;
            break;
        }
        case WM_LBUTTONUP:
        {
            mMouseButtonStatus[0] = KEY_UP;
            break;
        }
        case WM_RBUTTONUP:
        {
            mMouseButtonStatus[1] = KEY_UP;
            break;
        }
        case WM_MBUTTONUP:
        {
            mMouseButtonStatus[2] = KEY_UP;
            break;
        }
        case WM_CLOSE:
        {
            break;
        }

        case WM_DESTROY:
        {
            break;
        }
        break;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}