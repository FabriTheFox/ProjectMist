#include "MistEngine.h"
#include <iostream>

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void PrintSomething(const std::string& s, void* histance)
{


    // Register the window class.
    const char CLASS_NAME[] = "Window claaaazz";

    WNDCLASS wc = {};
    auto hist = GetModuleHandle(NULL);

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = (HINSTANCE)hist;
    wc.lpszClassName = CLASS_NAME;    

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "LMAO",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

                                        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        (HINSTANCE)hist,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);

    std::cout << s << std::endl;

    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}