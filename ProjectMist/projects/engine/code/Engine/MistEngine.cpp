#include <Engine/MistEngine.h>

namespace ME
{
    MistEngine::MistEngine() 
        : Terminal(*this)
        , Graphics(*this)
        , EntitySystem(*this)
    {

    }
}