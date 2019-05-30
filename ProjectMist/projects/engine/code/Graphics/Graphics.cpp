#include "Graphics.h"
#include <Windows.h>
#include <Engine/MistEngine.h>
#include <iostream>
#include <Graphics/RendererComp/RendererComp.h>

namespace ME
{
    void Graphics::Initialize()
    {
        mDeviceResources.CreateDeviceResources();
        mDeviceResources.CreateWindowResources((HWND)GetEngine().Terminal.GetWindow().m_WindowHandle);
        mDeviceResources.ConfigureBackBuffer();
    }

    void Graphics::Update()
    {
        for (auto& rend : mRenderables.mComponents)
        {
            static_cast<RendererComp*>(rend)->OnUpdate();
        }
    }

    void Graphics::Render()
    {
        for (auto& rend : mRenderables.mComponents)
        {
            static_cast<RendererComp*>(rend)->Render(&mDeviceResources);
        }

        mDeviceResources.Present();
    }

    void Graphics::RegisterComponent(RendererComp* renderer)
    {
        mRenderables.Register(renderer);
    }
}