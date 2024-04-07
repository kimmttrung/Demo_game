#include "Warrior.h"
#include "Texture.h"
#include <SDL2/SDL.h>

Warrior::Warrior(Properties* props): Character(props)
{
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1,8, 40,SDL_FLIP_HORIZONTAL);
    // m_Row = 1;
    // m_FrameCount = 8;
    // m_AnimSpeed = 25;
    
}


void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    //TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Warrior::Update(float dt)
{
    m_Animation->Update();
    //m_Frame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
// SDL_GetTicks: lay so mili giay khi khoi tao thu vien

