#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTextrue(const char* p_filePath);
    void CleanUp();
    void clear();
    void render(SDL_Texture* p_tex);
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};
