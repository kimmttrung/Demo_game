#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include<vector>

#include "RenderWindow.h"
#include "Entity.h"


int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed.SDL_ERROR: " << SDL_GetError() << std::endl;
    
    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Game treasure", 1280, 640);

    //SDL_Surface* tileMap = 
    //SDL_Texture* grassTexture = window.loadTextrue("map/3.png");
    SDL_Texture* tileMap = window.loadTextrue("img/tile4.png");

    
    int tilemap[80][10] = {
        7,7,7,7,7,2,1,1,1,1,    
        7,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,6,2,1,1,
        7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,7,7,2,1,1,
        7,7,7,7,7,2,1,1,1,1,
        4,7,7,7,7,7,7,2,1,1,
        4,7,7,7,7,7,6,2,1,1,

        4,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,2,1,1,1,1,
        7,7,6,7,7,2,1,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,

        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,4,2,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,6,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,6,2,1,1,1,

        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,2,1,1,1,1,
        7,7,6,7,7,2,1,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,

        7,7,7,7,2,1,1,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,6,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,6,2,1,1,1,

        4,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,2,1,1,1,1,
        7,7,6,7,7,2,1,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,

        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,4,2,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        4,7,7,7,7,6,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,
        4,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,6,2,1,1,1,

        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,2,1,1,1,1,
        7,7,6,7,7,2,1,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,6,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,7,7,2,1,1,1,
        7,7,7,7,2,1,1,1,1,1,


    };
    // for(int i=0;i<20;i++){
    //     for(int j=0;j<15;j++){
    //         tilemap[i][j] = rand() % 4 + 1;
    //     }
    // }

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

        // for(Entity& c : entities){
        //     window.render(c);
        // }
        //window.render(flatfrom0);
    
        SDL_Delay(10);

        static int setX = 0;
        
        if(keys[SDL_SCANCODE_RIGHT]){
            setX++;
            SDL_Delay(50);
        }
        if(keys[SDL_SCANCODE_LEFT]){
            setX--;
            SDL_Delay(50);
        }
        if(setX < 0){
            setX = 0;
        }
        if(setX > 60){
            setX = 60;
        }


        for(int i=0;i<20;i++){
            for(int j=0;j<10;j++){
                switch (tilemap[i+setX][j])
                {
                case 1:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_1,&tile[i][j]);
                    break;
                
                case 2:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_2,&tile[i][j]);
                    break;
                
                case 3:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_3,&tile[i][j]);
                    break;
                
                case 4:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_4,&tile[i][j]);
                    break;

                case 5:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_5,&tile[i][j]);
                    break;

                case 6:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_6,&tile[i][j]);
                    break;
                
                case 7:
                    SDL_RenderCopy(RenderWindow::renderer, tileMap,&select_tile_7,&tile[i][j]);
                    break;
                }
            }
        }

        window.display();
    }

    window.CleanUp();
    SDL_Quit();

    return 0;
}


