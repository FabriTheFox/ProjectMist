#pragma once

#ifdef MISTENGINE_DLL_EXPORT
    #define MISTENGINE_DLL __declspec(dllexport)
#else
    #define MISTENGINE_DLL __declspec(dllimport)
#endif