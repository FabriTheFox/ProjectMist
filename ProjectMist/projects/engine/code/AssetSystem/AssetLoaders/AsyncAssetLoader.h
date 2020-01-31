#pragma once

#include <atomic>
#include <AssetSystem/AssetSystem.h>
#include "AssetLoaderDefs.h"
#include <AssetSystem/Asset.h>

namespace ME
{
	class Asset;

	class AsyncAssetLoader
	{
	public:
		AsyncAssetLoader(Asset* defaultAsset = nullptr) { SetDefaultAsset(defaultAsset); }
		void SetDefaultAsset(Asset* defaultAsset = nullptr) { mAsset.store(defaultAsset); };

		template <typename T>
		void Load(Asset& asset, const String& source)
		{
			T& casted = static_cast<T&>(asset);
			AssetLoaders::LoadFromFile(casted, source);
			SwapWith(&casted);
		}

		Asset* GetAsset() const
		{
			return mAsset.load();
		}

		void SwapWith(Asset* asset) { mAsset.store(asset); }
	private:
		std::atomic<Asset*> mAsset;
	};
}