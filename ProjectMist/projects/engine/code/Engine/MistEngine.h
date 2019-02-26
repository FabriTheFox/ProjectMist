#pragma once

#include <string>

#ifdef MISTENGINE_DLL_EXPORT
    #define MISTENGINE_DLL __declspec(dllexport)
#else
    #define MISTENGINE_DLL __declspec(dllimport)
#endif

MISTENGINE_DLL void PrintSomething(const std::string& s, void* histance);