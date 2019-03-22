#include "Terminal.h"

RTTI_IMPLEMENTATION(ME::Terminal)

ME::Window& ME::Terminal::GetWindow()
{
    return m_Window;
}
