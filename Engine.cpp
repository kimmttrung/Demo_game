#include "Engine.h"
#include "Texture.h"
#include <iostream>
#include "Input.h"
#include "Warrior.h"
#include <SDL2/SDL.h>


Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init()
{
    bool check = true;
    if(SDL_Init(SDL_INIT_VIDEO) != 0 ){
        std::cout << "SDL_Init has failed.SDL_ERROR: " << SDL_GetError() << std::endl;
        check = false;
    }
    else{
        window = SDL_CreateWindow("Game treasure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if(window == nullptr)
        {
            std::cout << "Window failed to init.Eror: " << SDL_GetError() << std::endl;
            check = false;
        }

        m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        if(m_Renderer == nullptr){
            std::cout << "khong the tao ra Renderer: " << SDL_GetError() << std::endl; 
            check = false;
        }
        check = true;
    }

    TextureManager::GetInstance()->Load("player", "img/animation1.png");
    TextureManager::GetInstance()->Load("player", "img/animation1.png");

    player = new Warrior(new Properties("player", 0,0,120,135));

    Transform kim;
    kim.Log();

    return m_Running = true;
}

void Engine::Update()
{
    
    player->Update(0);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 10,6,6,255);// dăt mau sd cho thao tac ve
    SDL_RenderPresent(m_Renderer);

    player->Draw();
}
void Engine::Events()
{
    Input::GetInstance()->Listen();
}
void Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
void Engine::Quit()
{
    m_Running = false;

}
