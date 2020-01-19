#include <Engine/MistEngineDefs.h>
#include <Window/Terminal.h>
#include <EventSystem/EventSystem.h>

#include <Windows.h>

#include <iostream>

#include <vector>

#include "TestEvents.h"
#include <Engine/MistEngine.h>

#include <Libraries/Containers.h>
#include <EntitySystem/Entity/Entity.h>

#include <Graphics/RendererComp/RendererComp.h>

#include <Transform/Camera/Camera.h>
#include <Transform/Camera/FreeCamera.h>
#include "Graphics/Model/Model.h"
#include "Graphics/Shader/Shader.h"
#include "BuiltInAssets/Shaders/Shaders.h"

#include <AssetSystem/AssetSystem.h>
#include <AssetSystem/Assets/Texture.h>

int main()
{
    ME::MistEngine& e = ME::MistEngine::Get();
    e.Initialize();

    auto& t = e.Window;
    t.SetWindowName("Liya");

    auto& es = e.EntitySystem;
    auto& en = es.CreateEntity("Liya");
    auto& en2 = es.CreateEntity("Liya2");

    auto& g = e.Graphics;
    g.mCamera = &es.CreateEntity<ME::FreeCamera>("MainCamera");

    en.mTransform.mPosition.x = 1;
    en2.mTransform.mPosition.x = -1;


    ME::Model* cube = new ME::Model;
    ME::ShaderProgram* colorshader = new ME::ColorShader();
    {
        cube->Create(e.Graphics.mDeviceResources.m_pd3dDevice);

        auto* vs = new ME::VertexShader();
        auto* ps = new ME::PixelShader();

        vs->Create(e.Graphics.mDeviceResources.m_pd3dDevice, "", cube->mVertexLayout);
        ps->Create(e.Graphics.mDeviceResources.m_pd3dDevice, "");

        colorshader->SetVertexShader(vs);
        colorshader->SetPixelShader(ps);
        colorshader->CreateConstantBuffers(e.Graphics.mDeviceResources.m_pd3dDevice);
    }

    en.AddComponent(ME::RendererComp::sGetRTTI());
    auto& rcmp = en.GetComponent<ME::RendererComp>();
    rcmp.mCamera = g.mCamera;
    rcmp.mModel = cube;
    rcmp.mShader = colorshader;

    en2.AddComponent(ME::RendererComp::sGetRTTI());
    auto& rcmp2 = en2.GetComponent<ME::RendererComp>();
    rcmp2.mCamera = g.mCamera;
    rcmp2.mModel = cube;
    rcmp2.mShader = colorshader;

    e.AssetSystem.LoadAsset<ME::Texture>("Liya", "wallpaper.jpg");
    e.AssetSystem.LoadAsset<ME::Texture>("Sunset", "benny.png");

    while (true)
    {
        e.Update();
        Sleep(16);
    }

    e.ShutDown();

    return 0;
}
