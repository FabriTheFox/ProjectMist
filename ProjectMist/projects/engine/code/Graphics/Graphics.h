#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>
#include <Engine/Singleton.h>
#include <RTTI/RTTI.h>

namespace ME
{
    class Graphics
    {
    public:
        RTTI_DECLARATION(Graphics);
        SINGLETON_DEFCTOR_DLL(Graphics, MISTENGINE_DLL);

        void Initialize();

    private:
    };
}
