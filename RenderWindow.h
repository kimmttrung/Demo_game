#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.h"

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTextrue(const char* p_filePath);
    SDL_Surface* tileMap(const char* p_filePath);
    static SDL_Renderer* renderer;
    void CleanUp();
    void clear();
    void render(Entity& p_entity);
    void display();
private:
    SDL_Window* window;
    //SDL_Renderer* renderer;

};
