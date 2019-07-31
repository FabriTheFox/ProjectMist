#include "Window.h"

#include <Windows.h>
#include <Windowsx.h>

#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
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

ME::Window::Window()
    : m_WindowHandle(nullptr)
{
    dr = new DeviceResources;
}


#include <Graphics/Graphics.h>

#undef CreateWindow
void ME::Window::CreateTheWindow()
{
    // Register the window class.
    const char CLASS_NAME[] = "Window claaaazz";

    WNDCLASS wc = {};
    auto hist = GetModuleHandle(NULL);

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = (HINSTANCE)hist;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    BOOL menu = FALSE;
    RECT m_rc;
    int nDefaultWidth = 1280;
    int nDefaultHeight = 720;
    SetRect(&m_rc, 0, 0, nDefaultWidth, nDefaultHeight);
    AdjustWindowRect(
        &m_rc,
        WS_OVERLAPPEDWINDOW,
        menu
    );

    // Create the window.
    m_WindowHandle = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "LMAO",                         // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
                                        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 
        (m_rc.right - m_rc.left), (m_rc.bottom - m_rc.top),

        NULL,               // Parent window    
        NULL,               // Menu
        (HINSTANCE)hist,    // Instance handle
        NULL                // Additional application data
    );

    if (m_WindowHandle == NULL)
    {
        return;
    }

    ShowWindow((HWND)m_WindowHandle, SW_SHOWNORMAL);

    //dr->CreateDeviceResources();
    //dr->CreateWindowResources((HWND)m_WindowHandle);

    //Graphics::GetInstance().CreateShaders(dr->m_pd3dDevice);
    //Graphics::GetInstance().CreateBuffers(dr->m_pd3dDevice);
    //Graphics::GetInstance().CreateViewAndPerspective();
}

void ME::Window::SetWindowName(const String& name)
{
    m_WindowName = name;
}

const ME::String& ME::Window::GetWindowName()
{
    return m_WindowName;
}

void ME::Window::ProcessWindowMessages()
{
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //Graphics::GetInstance().Update();
    //Graphics::GetInstance().Render(dr->m_pd3dDeviceContext, dr->m_pRenderTarget, dr->m_pDepthStencilView, dr);

    //dr->Present();
}

