#pragma once

#include <DirectXMath.h>

namespace ME
{
    using Vec4 = DirectX::XMVECTOR;

    using FVec2 = DirectX::XMFLOAT2;
    using FVec3 = DirectX::XMFLOAT3;
    using FVec4 = DirectX::XMFLOAT4;

    using IVec2 = DirectX::XMINT2;
    using IVec3 = DirectX::XMINT3;
    using IVec4 = DirectX::XMINT4;

    using UVec2 = DirectX::XMUINT2;
    using UVec3 = DirectX::XMUINT3;
    using UVec4 = DirectX::XMUINT4;

    using Mat3 = DirectX::XMFLOAT3X3;
    using Mat4 = DirectX::XMFLOAT4X4;
}