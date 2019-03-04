#pragma once

#include <memory>

#define PTR_CAST(type)				\
	std::static_pointer_cast < type >

namespace ME
{
    template <typename T>
    using Ptr = std::shared_ptr < T >;

    template <typename T>
    using WPtr = std::weak_ptr < T >;

    template <typename T>
    using Uptr = std::unique_ptr < T >;
}