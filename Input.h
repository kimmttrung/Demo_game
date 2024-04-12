#pragma once
#include<SDL2/SDL.h>


class Input
{
    public:
        // thể hiện duy nhất của lớp Input
        static Input* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();
        }
        void Listen();
        bool GetKeyDown(SDL_Scancode key);// kiem tra mã 
        bool GetKeyUp(SDL_Scancode key);
        
        
    private:
        Input();// 1 constructor ngăn k tạo ở bên ngoài lớp
        void KeyUp();
        void KeyDown();
        

        const Uint8* m_KeyStates; // contro đến trạng thái các sự kiện phím
        static Input* s_Instance;// biến tĩnh

};