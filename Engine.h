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
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine(); // thể hiện duy nhất của lớp Engine
    }

    bool Init();// lõi, đồ họa ...
    void Quit();
    void Clean();

    void Events();
    void Update();
    void Render();// vẽ đối tượng

    inline bool Running() {return m_Running;}
    inline SDL_Renderer* GetRenderer(){return m_Renderer;}// trả về renderer để engine sd vẽ đồ họa
    inline SDL_Window* GetWindow(){return window;}
private:
    Engine(){}
    bool m_Running;

    SDL_Window* window;
    SDL_Renderer* m_Renderer;
    SDL_Surface* surface;
    static Engine* s_Instance;
    
};