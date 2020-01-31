#pragma once

#include <Engine/MistEngineDefs.h>
#include <RTTI/RTTI.h>
#include <Engine/System/System.h>
#include <AssetSystem/AssetLoaders/AsyncAssetLoader.h>

namespace ME
{
    class AssetRefBase : public IDynamic
    {
        RTTI_DECLARATION(AssetRefBase);
    public:
    };

    template <typename T>
    class AssetRef: public AssetRefBase
    {
        RTTI_DECLARATION(AssetRef<T>);
    public:
	private:
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
			AsyncAssetLoader& assetloader = assetmap[name];

			assetloader.SetDefaultAsset(nullptr);
			assetloader.Load<T>(*(new T()), path);
        }

        template <typename T>
        T& GetAsset(const String& name)
        {
            auto& assetmap = mAssets[T::sGetRTTI()];
			AsyncAssetLoader& assetloader = assetmap[name];

            return *(static_cast<T*>(assetloader.GetAsset()));
        }

    private:
		void LoadBuiltInAssets()
		{

		}

        using AssetMap = UnorderedMap<String, AsyncAssetLoader>;
        UnorderedMap<ME::RTTI, AssetMap> mAssets;

		UnorderedMap<ME::RTTI, SPtr<Asset>> mDefaultAssets;
    };

    RTTI_IMPLEMENTATION_TEMPLATE(AssetRef, T);
}