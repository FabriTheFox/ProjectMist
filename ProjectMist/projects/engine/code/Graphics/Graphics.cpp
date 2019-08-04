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
        ID3D11DeviceContext* context = mDeviceResources.m_pd3dDeviceContext;
        ID3D11RenderTargetView* renderTarget = mDeviceResources.m_pRenderTarget;
        ID3D11DepthStencilView* depthStencil = mDeviceResources.m_pDepthStencilView;;

        // Clear the render target and the z-buffer.
        const float teal[] = { 0.098f, 0.439f, 0.439f, 1.000f };
        context->ClearRenderTargetView(renderTarget, teal);
        context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        // Set the render target.
        context->OMSetRenderTargets(1, &renderTarget, depthStencil);

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