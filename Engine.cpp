#include "Engine.h"
#include "Texture.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;

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
    TextureManager::GetInstance()->Load("background3", "img/background3.jpg");
    return m_Running = true;
}

void Engine::Update()
{
    
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 255,255,117,0);
    SDL_RenderPresent(m_Renderer);

    TextureManager::GetInstance()->Draw("background3", 0, 0, 1500,1001);
}
void Engine::Events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch ((event.type)){
            case SDL_QUIT:
                Quit();
                break;
        }
    }
}
void Engine::Clean()
{
    TextureManager::GetInstance()->clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
void Engine::Quit()
{
    m_Running = false;

}
