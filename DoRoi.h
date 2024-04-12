#pragma once

#include "Vector.h"

#define UNI_MASS 0.5f   // khoi luong
#define GRAVITY 2.0f   // gia toc trong luc

#define FORWARD 1
#define BACKWARD -1

#define UPWARD 1
#define DOWNWARD -1



class RigidBody
{
    public:
        RigidBody(){
            m_Mass = UNI_MASS;      // khối lượng
            m_Gravity = GRAVITY;    // trong luc
        }
        // Setter trong luc va khoi luong: thiết lập
        inline void SetMass(float mass) {m_Mass = mass;}
        inline void SetGravity(float gravity) {m_Gravity = gravity;}

        // Force
        inline void ApplyForce(Vector F){m_Force = F;} // td lực F lên cơ thể cứng
        inline void ApplyForceX(float Fx){m_Force.X = Fx;} // td lực theo trục x
        inline void ApplyForceY(float Fy){m_Force.Y = Fy;} // td lực theo trục y
        inline void UnSetForce(){m_Force = Vector(0,0);} // loại bỏ, thực hiện lại

        // Ma sat
        inline void ApplyMaSat(Vector Fr){m_MaSat = Fr;}// td f ma sát
        inline void UnSetMaSat(){m_MaSat = Vector(0,0);}// loại bỏ ma sát

        //Getter
        inline float GetMass(){return m_Mass;}
        inline Vector ViTri(){return m_ViTri;}
        inline Vector VanToc(){return m_VanToc;}
        inline Vector GiaToc(){return m_Giatoc;}

        // update methode
        void Update(float dt){
            m_Giatoc.X = (m_Force.X + m_VanToc.X)/m_Mass;   // gx = (Fx + Vx)/m
            m_Giatoc.Y = m_Gravity + m_Force.Y/m_Mass;      // gy = gP + F/m
            m_VanToc = m_Giatoc*dt; // v = v0 + a*t
            m_ViTri = m_VanToc*dt; // x = v*t
        }

    private:
        float m_Mass;   // khoi luong
        float m_Gravity; // trong luong

        Vector m_Force;    //luc td
        Vector m_MaSat;

        Vector m_ViTri; // vi tri
        Vector m_VanToc; // van toc
        Vector m_Giatoc;// gia toc


};