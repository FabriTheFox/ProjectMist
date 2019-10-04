#include "Terminal.h"

#include <iostream>

// Win32 message handler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ME
{
    char Terminal::mKeyboardPrevious[VK_Count];
    char Terminal::mKeyboardCurrent[VK_Count];

    Terminal::Terminal()
    {
        memset(mKeyboardPrevious, 0, VK_Count);
        memset(mKeyboardCurrent, 0, VK_Count);
    }

    Terminal::~Terminal()
    {
    }

    bool Terminal::IsKeyDown(unsigned key)
    {
        return key < VK_Count && mKeyboardCurrent[key] == 1;
    }

    bool Terminal::IsKeyUp(unsigned key)
    {
        return key < VK_Count && mKeyboardCurrent[key] == 0;
    }

    LRESULT CALLBACK Terminal::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
            return true;

        switch (uMsg)
        {
        case WM_KEYDOWN:
        {
            if (wParam >= 0 && wParam < VK_Count)
            {
                mKeyboardCurrent[wParam] = 1;
            }
            break;
        }

        case WM_KEYUP:
        {
            if (wParam >= 0 && wParam < VK_Count)
            {
                mKeyboardCurrent[wParam] = 0;
            }
            break;
        }

        case WM_LBUTTONDOWN:
        {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);

            std::cout << "Left pressed: " << xPos << ", " << yPos << std::endl;
            break;
        }

        case WM_LBUTTONUP:
        {
            int xPos = GET_X_LPARAM(lParam);
            int yPos = GET_Y_LPARAM(lParam);

            std::cout << "Left lifted: " << xPos << ", " << yPos << std::endl;
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