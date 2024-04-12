#include "Engine.h"
#include "Texture.h"
#include "Input.h"
#include "Warrior.h"
#include <SDL2/SDL.h>
// #include "Timer.h"
#include <iostream>


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

    SDL_Surface* tile_map_surface = SDL_LoadBMP("img/tile4.bmp");
    SDL_Texture* tile_map_texture = SDL_CreateTextureFromSurface(m_Renderer, tile_map_surface);

    TextureManager::GetInstance()->Load("player", "img/animation1.png");
    TextureManager::GetInstance()->Load("player_Run", "img/animation1.png");

    player = new Warrior(new Properties("player", 100,200,120,135));

    // Transform kim;
    // kim.Log();


    int tilemap[80][10] = {
        7,7,7,7,7,2,1,1,1,1, 7,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,7,2,1,1, 4,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,6,2,1,1, 7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1, 7,7,7,7,2,1,1,1,1,1,
        4,7,7,7,7,7,7,2,1,1, 4,7,7,7,7,7,6,2,1,1,

        4,7,7,7,7,7,7,2,1,1, 7,7,7,7,7,7,7,2,1,1,
        7,7,6,7,7,7,7,2,1,1, 7,7,7,7,7,2,1,1,1,1,
        7,7,6,7,7,7,7,2,1,1, 7,7,7,7,7,2,1,1,1,1,
        7,7,6,7,7,7,7,2,1,1, 7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1, 7,7,7,7,7,7,7,2,1,1,

        7,7,7,7,7,7,7,2,1,1, 
        7,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,2,1,1,1,1, 
        7,7,6,7,7,7,7,8,8,1,
        4,7,7,7,7,2,1,1,1,1, 
        7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1, 
        7,7,7,7,7,7,7,2,1,1,
        4,7,7,6,7,7,7,2,1,1, 
        7,7,7,7,7,7,7,2,1,1,

        7,7,7,7,7,7,7,2,1,1, 7,7,7,7,7,7,7,2,1,1,
        7,7,2,7,7,7,7,2,1,1, 4,7,2,7,7,7,7,2,1,1,
        4,7,2,7,7,7,7,2,1,1, 7,7,2,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1, 7,7,6,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1, 4,7,7,7,7,7,2,1,1,1,

        7,7,7,7,7,2,1,1,1,1, 7,7,7,7,2,1,1,1,1,1,
        7,7,7,2,1,1,1,1,1,1, 4,7,2,1,1,1,1,1,1,1,
        4,7,7,7,7,7,7,8,8,1, 7,7,7,7,7,7,7,8,8,1,
        7,7,7,7,7,7,7,8,8,1, 4,7,7,6,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1, 4,7,2,1,1,1,1,1,1,1,

        7,7,7,7,7,7,7,8,8,1, 7,7,7,7,7,7,7,8,8,1,
        4,7,2,1,1,1,1,1,1,1, 7,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,7,2,1,1, 7,7,7,7,7,7,7,2,1,1,
        2,1,1,1,7,7,7,2,1,1, 2,1,1,1,7,7,7,2,1,1,
        2,1,1,1,7,7,7,2,1,1, 2,1,1,1,7,7,7,2,1,1,

        2,1,1,1,7,7,7,2,1,1, 2,1,1,1,7,7,7,2,1,1,
        4,7,7,7,7,4,7,2,1,1, 4,7,6,7,7,7,7,2,1,1,
        4,7,7,7,7,7,2,1,1,1, 7,7,2,1,7,7,2,1,1,1,
        7,7,2,1,7,7,2,1,1,1, 7,7,2,1,7,7,2,1,1,1,
        7,7,2,1,7,7,2,1,1,1, 7,7,2,1,7,7,2,1,1,1,

        7,7,7,7,7,7,7,2,1,1, 
        4,7,7,7,7,7,7,2,1,1,
        4,7,7,6,7,7,7,2,1,1, 
        4,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,2,1,1,1,1,
        7,7,7,7,7,7,7,2,1,1,
        4,7,6,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,2,1,1,1,1,

    };


    SDL_Rect tile[20][10];
    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++){
            tile[i][j].x = i * 64;
            tile[i][j].y = j * 64;
            tile[i][j].w = 64;
            tile[i][j].h = 64;
        }
    }

    
    SDL_Rect select_tile_1;
    select_tile_1.x = 0;
    select_tile_1.y = 0;
    select_tile_1.w = 64;
    select_tile_1.h = 64;

    SDL_Rect select_tile_2;
    select_tile_2.x = 64;
    select_tile_2.y = 0;
    select_tile_2.w = 64;
    select_tile_2.h = 64;

    SDL_Rect select_tile_3;
    select_tile_3.x = 128;
    select_tile_3.y = 0;
    select_tile_3.w = 64;
    select_tile_3.h = 64;

    SDL_Rect select_tile_4;
    select_tile_4.x = 0;
    select_tile_4.y = 64;
    select_tile_4.w = 64;
    select_tile_4.h = 64;

    SDL_Rect select_tile_5;
    select_tile_5.x = 64;
    select_tile_5.y = 64;
    select_tile_5.w = 64;
    select_tile_5.h = 64;

    SDL_Rect select_tile_6;
    select_tile_6.x = 128;
    select_tile_6.y = 64;
    select_tile_6.w = 64;
    select_tile_6.h = 64;

    SDL_Rect select_tile_7;
    select_tile_7.x = 0;
    select_tile_7.y = 128;
    select_tile_7.w = 64;
    select_tile_7.h = 64;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    static int setX = 0;
    if(keys[SDL_SCANCODE_RIGHT]){
        setX++;
        // SDL_Delay(50);
    }
    if(keys[SDL_SCANCODE_LEFT]){
        setX--;
        // SDL_Delay(50);
    }
    
    if(setX < 0){
        setX = 0;
    }
    if(setX > 100){
        setX = 100;
    }

    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++){
            switch (tilemap[i+setX][j])
            {
            case 1:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_1,&tile[i][j]);
                break;

            case 2:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_2,&tile[i][j]);
                break;

            case 3:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_3,&tile[i][j]);
                break;

            case 4:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_4,&tile[i][j]);
                break;

            case 5:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_5,&tile[i][j]);
                break;

            case 6:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_6,&tile[i][j]);
                break;

            case 7:
                SDL_RenderCopy(m_Renderer, tile_map_texture,&select_tile_7,&tile[i][j]);
                break;
            }
        }
    }
    return m_Running = true;

}

void Engine::Update()
{
    // float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(0);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124,218,254,255);// dăt mau sd cho thao tac ve
    SDL_RenderPresent(m_Renderer);

    player->Draw();
    SDL_RenderPresent(m_Renderer);
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
