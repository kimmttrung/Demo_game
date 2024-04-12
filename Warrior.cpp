#include "Warrior.h"
#include "Texture.h"
#include <SDL2/SDL.h>
#include "Input.h"
#include <iostream>
#include "Camera.h"

Warrior::Warrior(Properties* props): Character(props)
{
    m_RigiBody = new RigidBody(); // tạo 1 đối tượng mới RigidBody
    m_Animation = new Animation(); // tạo 1 đối tượng mới Animation
    m_Animation->SetProps(m_TextureID, 1, 4, 100); // khởi tạo để dùng cho animation
    
}


void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt)
{
    m_Animation->SetProps("player",1,4,200);
    m_RigiBody->UnSetForce(); // đứng lại

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_RigiBody->ApplyForceX(1*BACKWARD);
        m_Animation->SetProps("player_Run", 2, 4, 200, SDL_FLIP_HORIZONTAL);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_RigiBody->ApplyForceX(1*FORWARD);
        m_Animation->SetProps("player_Run", 2, 4, 200);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        m_RigiBody->ApplyForceY(0.1*UPWARD);
        m_Animation->SetProps("player_Run", 2, 4, 100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        m_RigiBody->ApplyForceY(0.1*DOWNWARD);
        m_Animation->SetProps("player_Run", 2, 4, 100);
        
    }
    std::cout << dt << std::endl;

    m_RigiBody->Update(0.4); // toc do 
    m_RigiBody->ApplyForceX(15); // áp dụng 1 lực cố định ban đầu cho nhân vật
    m_RigiBody->ApplyForceY(15);

    m_Transform->TranslateX(m_RigiBody->ViTri().X); // di chuyển nhân vật theo trục x
    //m_Transform->TranslateY(m_RigiBody->ViTri().Y);


    // camera
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
    Camera::GetInstance()->SetTarget(m_Origin);
    
   
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}
// SDL_GetTicks: lay so mili giay khi khoi tao thu vien

