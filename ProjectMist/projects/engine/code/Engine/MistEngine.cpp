#include <Engine/MistEngine.h>

namespace ME
{
    MistEngine::MistEngine() 
        : Window(*this)
        , Graphics(*this)
        , EntitySystem(*this)
    {

    }
}