#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.h"

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed.SDL_ERROR: " << SDL_GetError() << std::endl;
    
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Game treasure", 1280, 700);
    SDL_Texture* grassTexture = window.loadTextrue("background2.jpg");

    bool gameRun = true;

    SDL_Event event;

    while(gameRun)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                gameRun = false;
        }

        window.clear();
        window.render(grassTexture);
        window.display();
    }
    window.CleanUp();
    SDL_Quit();

    return 0;
}


