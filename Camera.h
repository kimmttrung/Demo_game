#pragma once

#include "Point.h"


class Camera {
    public:
        inline static Camera* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Camera();
        }

    private:
        Camera(){}

        static Camera* s_Instance;

};