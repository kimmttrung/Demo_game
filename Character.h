#pragma once

#include "GameObject.h"
#include <string>

class Character : public GameObject // kế thừa lớp GameObject
{
    public:
        Character(Properties* props): GameObject(props) {} // gọi hàm tạo của lớp cha GameObject với tham số props

        virtual void Draw() = 0; // hàm ảo thuần túy bắt buộc các lớp con phải cung cấp cài đặt
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;
    protected:
        std::string m_Name;

};

// virtul: cho phép các lớp con ghi đè lên hàm ảo của lớp cha