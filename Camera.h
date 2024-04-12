#pragma once

#include "Point.h"
#include <SDL2/SDL.h>
#include "Vector.h"
#include "Engine.h"


class Camera {
    public:
        void Update(float dt);// trạng thái camera(vị trí, thuộc tính ) trong tg trôi dt
        inline SDL_Rect GetViewBox(){return m_ViewBox;}// phạm vi hiển thị của camera
        inline Vector GetPosition(){return m_Position;}// vị trí hiện tại 
        inline void SetTarget(Point* target){m_Target = target;}// mục tiêu camera hướng đến
        inline static Camera* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Camera();// duy nhat 1 chuong trinh camera chạy
        }

    private:
        Camera(){m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};}

        Point* m_Target; // vị trí đối tượng camera hướng đến
        Vector m_Position; // vị trí camera hiện tại

        SDL_Rect m_ViewBox; // phạm vi hiển thị của camera
        static Camera* s_Instance; 

};