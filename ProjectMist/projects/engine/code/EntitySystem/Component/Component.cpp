#include "Component.h"
#include <EntitySystem/Entity/Entity.h>

namespace ME
{
    Component::Component(Entity* owner)
    {
        mOwner = owner;
    }

    Transform3D& Component::GetTransform()
    {
        return mOwner->mTransform;
    }
}