#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

class Engine
{
public:
    static Engine* GetInstance(){
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
    }

    bool Init();
    void Clean();
    void Quit();

    void Events();
    void Update();
    void Render();

    inline bool Running() {return m_Running;}
    inline SDL_Renderer* GetRenderer(){return m_Renderer;}
    inline SDL_Window* GetWindow(){return window;}
private:
    Engine(){}
    bool m_Running;

    SDL_Window* window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
    
};