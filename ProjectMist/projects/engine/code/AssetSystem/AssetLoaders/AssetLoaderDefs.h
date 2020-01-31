#pragma once

#include <AssetSystem/Assets/Texture.h>
#include <Engine/MistEngineDefs.h>

namespace ME
{
	namespace AssetLoaders
	{
		MISTENGINE_DLL void LoadFromFile(ME::Texture& tex, const String& filepath);
	}
}