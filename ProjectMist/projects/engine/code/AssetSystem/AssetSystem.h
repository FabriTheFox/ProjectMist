#pragma once

#include <Engine/MistEngineDefs.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>

namespace ME
{
    class Texture
    {
    public:

    };

    class AssetSystem : public System
    {
        SYSTEM_DECLARATION(AssetSystem);

    public:
        void OnInitialize() override final;
        void OnUpdate() override final;

        void LoadTexture(const String& path, const String& name);
        const Texture& GetTexture(const String& name);

    private:
        UnorderedMap<String, Texture> mTextures;
    };
}