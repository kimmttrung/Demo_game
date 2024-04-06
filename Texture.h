#pragma once

#include<string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map> 

class TextureManager
{
public: 
    static TextureManager* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}
    
    bool Load(std::string id, std::string filename);
    void Drop(std::string id); // xoa ket cau
    void clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE); // sd lat cho doi tuong

private:
    TextureManager(){};
    std::map <std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_Instance;

};