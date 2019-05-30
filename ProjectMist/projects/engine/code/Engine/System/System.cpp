#include <Engine/System/System.h>
#include <EntitySystem/Component/Component.h>

namespace ME
{
    void CompPointerVector::Register(Component* ptr)
    {
        mComponents.push_back(ptr);
    }

    void CompPointerVector::DeleteDead()
    {
        for (unsigned i = 0; i < mComponents.size(); ++i)
        {
            if (mComponents[i]->IsMarkedForDeletion())
            {
                mComponents[i] = mComponents.back();
                mComponents.pop_back();
            }
        }
    }
}