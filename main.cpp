#include "func.h"
// #include "BaseObject.h"
#include "PrintScreen.h"


extern SDL_Window* g_Window;   // cua so hien thi
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gHelloWorld;

int main(int argc, char* argv[])
{
    if(!init())
        return -1;
    else
    {
        if(!LoadBackground())
        {
            return -1;
        }
        else
        {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface( g_Window );
        }
    }
    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
    close();
    return 0;
}
