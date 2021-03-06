#pragma once

#include <memory>

#define PTR_CAST(type)				\
	std::static_pointer_cast < type >

#define UNUSED_PARAM(type)          \
    (void)(type)

namespace ME
{
    template <typename T>
    using SPtr = std::shared_ptr < T >;

    template <typename T>
    using WPtr = std::weak_ptr < T >;

    template <typename T>
    using UPtr = std::unique_ptr < T >;
}