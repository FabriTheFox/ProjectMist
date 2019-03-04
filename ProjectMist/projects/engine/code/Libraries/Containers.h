#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>

namespace ME
{
    using String = std::string;

    template <typename T>
    using Vector = std::vector<T>;

    template <typename T>
    using List = std::list<T>;

    template <typename T, typename U>
    using Map = std::map<T, U>;

    template <typename T, typename U>
    using UnorderedMap = std::unordered_map<T, U>;
}

