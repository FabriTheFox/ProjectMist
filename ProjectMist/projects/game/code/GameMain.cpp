#include <Engine/MistEngine.h>
#include <Terminal/Terminal.h>
#include <EventSystem/EventSystem.h>

#include <Windows.h>

#include <iostream>

#include <vector>

class MyEvent : public ME::Event
{
public:
    int MyData;
};

class MyListener : public ME::EventListener
{
public:
    virtual void OnEvent(const MyEvent& ev)
    {
        std::cout << "LMAO" << std::endl;
    }
};

int main()
{

    MyListener lis;
    ME::EventSystem::GetInstance().m_Listeners = &lis;

    MyEvent EV;
    EV.MyData = 89;

    ME::EventSystem::GetInstance().DispatchEvent<MyEvent>(EV);

    //auto& i = t.getInt();

    //t.GetWindow().SetWindowName("Liya");
    //auto& w = t.GetWindow();
    //w.CreateTheWindow();

    return 0;
}
