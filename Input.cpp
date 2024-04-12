#include "Input.h"
#include "Engine.h"

Input* Input::s_Instance = nullptr;// khởi tạo biến tĩnh

Input::Input()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);// trạng thái hiện tại của bàn phím.
}
void Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT: Engine::GetInstance()->Quit();break;
            case SDL_KEYUP: KeyUp(); break;
            case SDL_KEYDOWN: KeyDown(); break;
            // case SDL_KEYRIGHT: KeyRight(); break;
            // case SDL_LEFT(); break;
        }
    }
}
// SDL_Scancode: mã quét bàn phím
bool Input::GetKeyDown(SDL_Scancode key)
{
    if(m_KeyStates[key] == 1)
        return true;
    return false;
}
bool Input::GetKeyUp(SDL_Scancode key)
{
    if(m_KeyStates[key] == 1)
        return true;
    return false;
}
void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}
void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}