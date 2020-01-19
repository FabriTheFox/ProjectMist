#pragma once

#include <Engine/MistEngineDefs.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>

namespace ME
{
    class AssetHandlerBase : public IDynamic
    {
        RTTI_DECLARATION(AssetHandlerBase);
    public:
    };

    template <typename T>
    class AssetHandler : public AssetHandlerBase
    {
        RTTI_DECLARATION(AssetHandler<T>);
    public:
        
    };

    class Asset : public IDynamic
    {
    public:
        virtual void Load(const String& path) = 0;
    };

    class MISTENGINE_DLL AssetSystem : public System
    {
        SYSTEM_DECLARATION(AssetSystem);

    public:
        void OnInitialize() override final;
        void OnUpdate() override final;

        template <typename T>
        void LoadAsset(const String& name, const String& path)
        {
            auto& assetmap = mAssets[T::sGetRTTI()];
            auto& asset = assetmap[name];
            asset = std::make_shared<T>();
            asset->Load(path);
        }

        template <typename T>
        T& GetAsset(const String& name)
        {
            auto& assetmap = mAssets[T::sGetRTTI()];
            return *(PTR_CAST(T)(assetmap[name]));
        }

    private:
        using AssetMap = UnorderedMap<String, SPtr<Asset>>;
        UnorderedMap<ME::RTTI, AssetMap> mAssets;
    };

    RTTI_IMPLEMENTATION_TEMPLATE(AssetHandler, T);
}