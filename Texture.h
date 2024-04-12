#pragma once

#include<string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map> 

class TextureManager
{
public: 
    // duy nhất của lớp TextureManager
    static TextureManager* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}
    
    bool Load(std::string id, std::string filename); // load texture từ file và lưu nó vào m_TextureMap
    void Drop(std::string id); // xoa texture có id tương ứng
    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE); // vẽ texture
    
    // vẽ khung hình texture kèm hàng và số lượng frame
    void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    
    
private:
    TextureManager(){};
    std::map <std::string, SDL_Texture*> m_TextureMap; // key là id và value là texture
    static TextureManager* s_Instance;

};