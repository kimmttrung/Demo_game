#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window* m_Window = NULL;
SDL_Surface* m_Surface = NULL;
SDL_Surface* g_Background = NULL;


bool loadMedia()
{
    bool success = true;
    g_Background = IMG_Load("img/background3.jpg");
    if (g_Background == NULL)
    {
        std::cout << "Khong the load background " << "! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}

void close()
{
    SDL_FreeSurface(g_Background);
    g_Background = NULL;
    
    SDL_DestroyWindow(m_Window);
    m_Window = NULL;
    SDL_Quit();
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 640, SDL_WINDOW_SHOWN);

    if(m_Window != NULL)
    { 
        m_Surface = SDL_GetWindowSurface(m_Window);
    }
    return success;
}

int main(int argc, char* argv[])
{
    if(init() == true)
    {
        if(loadMedia())
        {
            SDL_BlitSurface(g_Background, NULL, m_Surface, NULL);
            SDL_UpdateWindowSurface(m_Window);
            SDL_Delay(5000);
        }
    }
    
          
    close();
    return 0;
}
