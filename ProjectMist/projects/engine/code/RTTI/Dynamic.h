#pragma once

#include <RTTI/RTTI.h>

namespace ME
{
    class FTF_Base
    {
    public:
        virtual RTTI& GetRTTI() const = 0;
    protected:
        
    };
}

