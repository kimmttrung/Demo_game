#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "Entity.h"

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed.SDL_ERROR: " << SDL_GetError() << std::endl;
    
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Game treasure", 1400, 1000);
    SDL_Texture* grassTexture = window.loadTextrue("img/tileMap1.png");

    Entity entities[3] =    {Entity(0, 0, grassTexture),
                            Entity(50,0, grassTexture),
                            Entity(50,50, grassTexture)};
    //Entity flatfrom0(0, 0, grassTexture);

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

        for(int i=0;i<3;i++){
            window.render(entities[i]);
        }
        //window.render(flatfrom0);
        
        window.display();
    }
    window.CleanUp();
    SDL_Quit();

    return 0;
}


