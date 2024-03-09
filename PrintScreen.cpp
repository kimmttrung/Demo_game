
#include "PrintScreen.h"

SDL_Window* g_Window = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;
    else
    {
        g_Window = SDL_CreateWindow("huong dan SDL",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SCREEN_WIDTH, SCREEN_HEIGHT, 
                                    SDL_WINDOW_SHOWN);

        if(g_Window == NULL)
        {
            printf( "Không thể tạo cửa sổ! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(g_Window);
        }
    }
    return success;
}

bool LoadBackground()
{
    
    bool success = true;
    gHelloWorld = IMG_Load("img//chess1.png");
    if (gHelloWorld == NULL)
    {
        printf( "Không the tai hinh anh %s! Lỗi SDL: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
        success = false;
    }
    return success;
}

void close()
{
    // phan bo be mat
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // pha huy cua so
    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    SDL_Quit();
}