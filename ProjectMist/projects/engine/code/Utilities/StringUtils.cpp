#include <MistEngine_PCH.h>
#include "StringUtils.h"

namespace ME
{
    void StringToWide(const std::string& s, std::wstring& out)
    {
        int len;
        int slength = (int)s.length() + 1;
        len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
        wchar_t* buf = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
        out = buf;
        delete[] buf;
    }
}