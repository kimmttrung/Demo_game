#pragma once

#include "Character.h"
#include "Animation.h"
#include "DoRoi.h"


class Warrior: public Character // kế thừa lớp Character
{

    public:
        Warrior(Properties* props);
        virtual void Draw();
        virtual void Update(float dt) ;
        virtual void Clean();

    private:
        Animation* m_Animation; // con trỏ đến lớp Animation
        RigidBody* m_RigiBody;  // con trỏ đến lớp RigidBody
};

// virtual: cho phép các lớp con ghi đè lên hàm ảo của lớp cha