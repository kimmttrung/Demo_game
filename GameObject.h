#pragma once
#include <SDL2/SDL.h>
//#include "Iobject.h"
#include "Transform.h"
#include <iostream>
#include <string>
#include "Point.h"

struct Properties{
    public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE){
            X = x;                          //SDL_RendererFlip : sd để lật animation
            Y = y;
            Flip = flip;    // trạng thái lật
            Width = width;
            Height = height;
            TextureID = textureID;// dịa chỉ id;
        }

        std::string TextureID;
        int Width, Height;
        float X, Y;
        SDL_RendererFlip Flip;
};

class GameObject //: public Iobject
{
    public:
        // khởi tạo các thuộc tính của đối tượng dựa trên một đối tượng Propertie
        GameObject(Properties* props) : m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip)
        {
            m_Transform = new Transform(props->X, props->Y); // vị trí mới

            // camera nhan vat
            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_Origin = new Point(px, py);
        }

        inline Point* GetOrigin(){return m_Origin;}

        virtual void Draw() = 0;                // vẽ đối tượng
        virtual void Update(float dt) = 0;     // cập nhật đối tượng
        virtual void Clean() = 0;

    protected:
        Point* m_Origin;// vị trí camera
        
        Transform* m_Transform;
        int m_Width, m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;

};