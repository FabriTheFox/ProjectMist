#include "Window.h"

#include <Windows.h>
#include <Windowsx.h>

#include <iostream>

#include <External/Imgui/imgui.h>
#include <External/Imgui/imgui_impl_win32.h>
#include <External/Imgui/imgui_impl_dx11.h>

#include <Window/Terminal.h>

namespace ME
{
#include <Graphics/Graphics.h>

#undef CreateWindow
    void Window::CreateTheWindow()
    {
        mDeviceResources = new DeviceResources;

        // Register the window class.
        const char CLASS_NAME[] = "Window claaaazz";

        WNDCLASS wc = {};
        auto hist = GetModuleHandle(NULL);

        wc.lpfnWndProc = Terminal::WindowProc;
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
        mWindowHandle = CreateWindowEx(
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

        if (mWindowHandle == NULL)
        {
            return;
        }

        ShowWindow((HWND)mWindowHandle, SW_SHOWNORMAL);

        //dr->CreateDeviceResources();
        //dr->CreateWindowResources((HWND)m_WindowHandle);

        //Graphics::GetInstance().CreateShaders(dr->m_pd3dDevice);
        //Graphics::GetInstance().CreateBuffers(dr->m_pd3dDevice);
        //Graphics::GetInstance().CreateViewAndPerspective();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Read 'misc/fonts/README.txt' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        //io.Fonts->AddFontDefault();
        io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 22.0f);
        io.Fonts->AddFontFromFileTTF("fonts/Cousine-Regular.ttf", 15.0f);
        io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", 16.0f);
        io.Fonts->AddFontFromFileTTF("fonts/ProggyTiny.ttf", 10.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != NULL);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer bindings
        ImGui_ImplWin32_Init(mWindowHandle);
    }

    void Window::SetWindowName(const String& name)
    {
        mWindowName = name;
    }

    void Window::OnInitialize()
    {
        CreateTheWindow();
    }

    void Window::OnUpdate()
    {
        ProcessWindowMessages();
    }

    void Window::OnShutdown()
    {

    }

    void Window::ProcessWindowMessages()
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

}