#include "MistEngine_PCH.h"

#include "Graphics.h"
#include <Engine/MistEngine.h>
#include <iostream>
#include <Graphics/RendererComp/RendererComp.h>
#include <Transform/Camera/Camera.h>

#include <External/Imgui/imgui.h>
#include <External/Imgui/imgui_impl_win32.h>
#include <External/Imgui/imgui_impl_dx11.h>

namespace ME
{
    void Graphics::OnInitialize()
    {
        mDeviceResources.CreateDeviceResources();
        mDeviceResources.CreateWindowResources((HWND)GetEngine().Window.GetWindowHandle());
        mDeviceResources.ConfigureBackBuffer();

        ImGui_ImplDX11_Init(mDeviceResources.m_pd3dDevice, mDeviceResources.m_pd3dDeviceContext);
    }

    void Graphics::OnUpdate()
    {
        for (auto& rend : mRenderables.mComponents)
        {
            static_cast<RendererComp*>(rend)->OnUpdate();
        }
    }

    void Graphics::OnShutdown()
    {
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

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        static bool open = true;
        ImGui::ShowDemoWindow(&open);

        // Set the render target.
        context->OMSetRenderTargets(1, &renderTarget, depthStencil);

        mCamera->UpdateMatrices();
        for (auto& rend : mRenderables.mComponents)
        {
            static_cast<RendererComp*>(rend)->Render(&mDeviceResources);
        }

        ImGui::Render();
        context->OMSetRenderTargets(1, &renderTarget, depthStencil);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        mDeviceResources.Present();
    }

    void Graphics::RegisterComponent(RendererComp* renderer)
    {
        mRenderables.Register(renderer);
    }
}