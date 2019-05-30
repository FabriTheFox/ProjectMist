#pragma once

#include <d3d11_4.h>
#include <Engine/MistEngineDefs.h>

namespace ME
{
    class MISTENGINE_DLL DeviceResources
    {
    public:
        DeviceResources();
        ~DeviceResources();

        HRESULT CreateDeviceResources();
        HRESULT CreateWindowResources(HWND hWnd);

        HRESULT ConfigureBackBuffer();
        HRESULT ReleaseBackBuffer();
        HRESULT GoFullScreen();
        HRESULT GoWindowed();

        float GetAspectRatio();

        ID3D11Device*           GetDevice() { return m_pd3dDevice; };
        ID3D11DeviceContext*    GetDeviceContext() { return m_pd3dDeviceContext; };
        ID3D11RenderTargetView* GetRenderTarget() { return m_pRenderTarget; }
        ID3D11DepthStencilView* GetDepthStencil() { return m_pDepthStencilView; }

        void Present();

        //private:

        //-----------------------------------------------------------------------------
        // Direct3D device
        //-----------------------------------------------------------------------------
        ID3D11Device*        m_pd3dDevice;
        ID3D11DeviceContext* m_pd3dDeviceContext; // immediate context
        IDXGISwapChain*      m_pDXGISwapChain;


        //-----------------------------------------------------------------------------
        // DXGI swap chain device resources
        //-----------------------------------------------------------------------------
        ID3D11Texture2D*        m_pBackBuffer;
        ID3D11RenderTargetView* m_pRenderTarget;


        //-----------------------------------------------------------------------------
        // Direct3D device resources for the depth stencil
        //-----------------------------------------------------------------------------
        ID3D11Texture2D*         m_pDepthStencil;
        ID3D11DepthStencilView*  m_pDepthStencilView;


        //-----------------------------------------------------------------------------
        // Direct3D device metadata and device resource metadata
        //-----------------------------------------------------------------------------
        D3D_FEATURE_LEVEL       m_featureLevel;
        D3D11_TEXTURE2D_DESC    m_bbDesc;
        D3D11_VIEWPORT          m_viewport;
    };
}

