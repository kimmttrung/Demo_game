#pragma once
#include<SDL2/SDL.h>


class Input
{
    public:
        static Input* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();
        }
        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        bool GetKeyUp(SDL_Scancode key);
        // bool GetKeyRight(SDL_Scancode key);
        // bool GetKeyLeft(SDL_Scancode key);
        
    private:
        Input();
        void KeyUp();
        void KeyDown();
        // void KeyRight();
        // void KeyLeft();

        const Uint8* m_KeyStates;
        static Input* s_Instance;

};