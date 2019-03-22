#include <Engine/MistEngineDefs.h>
#include <Terminal/Terminal.h>
#include <EventSystem/EventSystem.h>

#include <Windows.h>

#include <iostream>

#include <vector>



int main()
{
    




    auto& t = ME::Terminal::GetInstance();
    t.GetWindow().SetWindowName("Liya");
    auto& w = t.GetWindow();
    w.CreateTheWindow();

    while (true)
    {
        w.ProcessWindowMessages();
    }

    return 0;
}
