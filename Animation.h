#pragma once

#include <string>
#include <SDL2/SDL.h>


class Animation{
    public:
        Animation(){}

        void Update();// trang thai animation
        void Draw(float x, float y, int spriteWidth, int spriteHeight);// ve animation
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip=SDL_FLIP_NONE);

    private:
        int m_SpriteRow, m_SpriteFrame;// so hang 
        int m_AnimSpeed, m_FrameCount;// toc do va so luong
        std::string m_TextureID;  // id
        SDL_RendererFlip m_Flip;  // trai phai


};
