#include <Engine/MistEngine.h>
#include <Windows.h>

#include <iostream>

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
){
    PrintSomething("Hello from game", hInstance);
}