#include <iostream>
#include "ComFun.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"


BaseObject g_background;

bool InitData()
{
    bool success = true;
    // khoi tao SDL
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    g_Window = SDL_CreateWindow("Game treasure std - kim1",
                                SDL_WINDOWPOS_UNDEFINED,   // vi tri cua screen
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);

    if(g_Window == NULL)
    {
        std::cout << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // tao render de ve hinh anh len sreeen
        // SDL_RENDERER_ACCELERATED: tang toc do phan ung
        g_screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            // sd mau cho thao tac ve
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;    
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/Bground1.jpg", g_screen);
    if(ret == false)
        return false;
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{ 
    if(InitData() == false)
        return -1;
    if(LoadBackground() == false)
        return -1;


    GameMap game_map;// khai bao map
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    game_map.LoadMap("map1/map012.dat");// load map
    #pragma GCC diagnostic warning "-Wwrite-strings"
    game_map.LoadTiles(g_screen);// load hinh anh cho map

    MainObject p_player;// khai bao animation
    p_player.LoadImg("img/player_right.png", g_screen);
    p_player.set_clips();

    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_Event) != 0)
        {
            if(g_Event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputAction(g_Event, g_screen);// xử lý di chuyển nhân vật
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);

        p_player.Show(g_screen);// hiển thị nhân vật

        
        SDL_RenderPresent(g_screen);
    }
    
    close();
    return 0;
}
