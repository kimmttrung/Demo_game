#include <iostream>
#include "ComFun.h"
#include "BaseObject.h"


BaseObject g_background;

bool InitData()
{
    bool success = true;
    // khoi tao SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
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
        g_Screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
        if (g_Screen == NULL)
            success = false;
        else
        {
            // sd mau cho thao tac ve
            SDL_SetRenderDrawColor(g_Screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;    
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/Bground.png", g_Screen);
    if(ret == false)
        return false;
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_Screen);
    g_Screen = NULL;

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

    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_Event) != 0)
        {
            if(g_Event.type == SDL_QUIT)
            {
                is_quit = true;
            }
        }

        SDL_SetRenderDrawColor(g_Screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_Screen);

        g_background.Render(g_Screen);

        SDL_RenderPresent(g_Screen);
    }
    

    return 0;
}
