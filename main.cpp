#include <iostream>
#include "Engine.h"



int main(int argc, char* argv[])
{
    Engine::GetInstance()->Init();
    while(Engine::GetInstance()->Running()){
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        //Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}


