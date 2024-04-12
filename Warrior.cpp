#include "Warrior.h"
#include "Texture.h"
#include <SDL2/SDL.h>
#include "Input.h"
#include <iostream>

Warrior::Warrior(Properties* props): Character(props)
{
    m_RigiBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1,4, 100);
    
}


void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_Animation->SetProps("player",1,4,100);
    m_RigiBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_RigiBody->ApplyForceX(0.1*BACKWARD);
        m_Animation->SetProps("player_Run", 2, 4, 100, SDL_FLIP_HORIZONTAL);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_RigiBody->ApplyForceX(0.1*FORWARD);
        m_Animation->SetProps("player_Run", 2, 4, 100);
    }
    std::cout << dt << std::endl;

    m_RigiBody->Update(0.7); // toc do 
    m_RigiBody->ApplyForceX(10);

    m_Transform->TranslateX(m_RigiBody->ViTri().X);
    //m_Transform->TranslateY(m_RigiBody->ViTri().Y);
    m_Animation->Update();
   
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
// SDL_GetTicks: lay so mili giay khi khoi tao thu vien

