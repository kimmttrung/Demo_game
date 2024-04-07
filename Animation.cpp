#include "Animation.h"
#include "Texture.h"


void Animation::Update(){
    m_SpriteFrame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureID = textureID;// dia chi
    m_SpriteRow = spriteRow; // hang
    m_FrameCount = frameCount; // so luong
    m_AnimSpeed = animSpeed; // toc do 
    m_Flip = flip;
}