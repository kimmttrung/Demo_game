#pragma once

#include "Vector.h"

#define UNI_MASS 0.5f   // khoi luong
#define GRAVITY 9.8f   // trong luc

class RigidBody
{
    public:
        RigidBody(){
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY;
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
        inline Vector Position(){return m_Position;}
        inline Vector Veclocity(){return m_Velocity;}
        inline Vector Accelaration(){return m_Accelaration;}

        // update methode
        void Update(float dt){
            m_Accelaration.X = (m_Force.X + m_Velocity.X)/m_Mass;
            m_Accelaration.Y = m_Gravity + m_Force.Y/m_Mass;
            m_Velocity = m_Accelaration*dt;
            m_Position = m_Velocity*dt;
        }

    private:
        float m_Mass;   // khoi luong
        float m_Gravity; // trong luong

        Vector m_Force;
        Vector m_MaSat;

        Vector m_Position; // vi tri
        Vector m_Velocity; // toc do
        Vector m_Accelaration;// gia toc


};