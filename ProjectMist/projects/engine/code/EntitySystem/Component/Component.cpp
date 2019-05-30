#include "Component.h"

namespace ME
{
    Component::Component(Entity* owner)
    {
        mOwner = owner;
    }
}