#pragma once

#include "Vector.h"

#define UNI_MASS 1.0f   // khoi luong
#define GRAVITY 10.0f   // gia toc trong luc

#define FORWARD 1
#define BACKWARD -1

#define UPWARD 1
#define DOWNWARD -1

class RigidBody
{
    public:
        RigidBody(){
            m_Mass = UNI_MASS;  // luc hap dan
            m_Gravity = GRAVITY;    // trong luc
        }
        // Setter trong luc va khoi luong
        inline void SetMass(float mass) {m_Mass = mass;}
        inline void SetGravity(float gravity) {m_Gravity = gravity;}

        // Force
        inline void ApplyForce(Vector F){m_Force = F;}
        inline void ApplyForceX(float Fx){m_Force.X = Fx;}
        inline void ApplyForceY(float Fy){m_Force.Y = Fy;}
        inline void UnSetForce(){m_Force = Vector(0,0);}

        // Ma sat
        inline void ApplyMaSat(Vector Fr){m_MaSat = Fr;}
        inline void UnSetMaSat(){m_MaSat = Vector(0,0);}

        //Getter
        inline float GetMass(){return m_Mass;}
        inline Vector ViTri(){return m_ViTri;}
        inline Vector VanToc(){return m_VanToc;}
        inline Vector GiaToc(){return m_Giatoc;}

        // update methode
        void Update(float dt){
            m_Giatoc.X = (m_Force.X + m_VanToc.X)/m_Mass;
            m_Giatoc.Y = m_Gravity + m_Force.Y/m_Mass;
            m_VanToc = m_Giatoc*dt;
            m_ViTri = m_VanToc*dt;
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