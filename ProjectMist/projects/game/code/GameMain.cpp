#include <Engine/MistEngine.h>
#include <Terminal/Terminal.h>

#include <Windows.h>

#include <iostream>

#include <vector>

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
){

    PrintSomething("Hello from game", hInstance);

    auto& t = ME::Terminal::GetInstance();

    //auto& i = t.getInt();

    //t.GetWindow().SetWindowName("Liya");
    auto& w = t.GetWindow();
    w.CreateTheWindow();

    return 0;
}
