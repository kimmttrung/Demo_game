#include "Warrior.h"
#include "Texture.h"
#include <SDL2/SDL.h>
#include "Input.h"


Warrior::Warrior(Properties* props): Character(props)
{
    m_RigiBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1,4, 100,SDL_FLIP_HORIZONTAL);
    
}


void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_Animation->SetProps(m_TextureID,1,4,100);
    m_RigiBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_RigiBody->ApplyForceX(1);
        m_Animation->SetProps("Run2.2", 2, 4, 100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_RigiBody->ApplyForceX(1);
        m_Animation->SetProps("Run2.2", 2, 4, 100);
    }

    m_RigiBody->Update(0.05);
    m_RigiBody->ApplyForceX(10);
    m_Transform->TranslateX(m_RigiBody->Position().X);
    //m_Transform->TranslateY(m_RigiBody->Position().Y);
    m_Animation->Update();
   
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
// SDL_GetTicks: lay so mili giay khi khoi tao thu vien

