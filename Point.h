#pragma once


#include <iostream>

class Point
{
    public:
        float X, Y;

    public:
        Point(float x, float y): X(x), Y(y){}

        inline Point operator+(const Point& p) const{
            return Point(X + p.X, Y + p.Y);
        }

        inline friend Point operator+=(Point& p1, const Point& p2){
            p1.X += p2.X;
            p1.Y += p2.Y;
            return p1;
        }
        inline Point operator-(const Point& p) const{
            return Point(X - p.X, Y - p.Y);
        }
        inline friend Point operator-=(Point& p1, const Point& p2){
            p1.X -= p2.X;
            p1.Y -= p2.Y;
            return p1;
        }
        inline Point operator*(const float& f) const{
            return Point(X * f, Y * f);
        }
        
        void Log(std::string msg = ""){
            std::cout << msg << "(X, Y) = " << "(" << X << "," << Y << ")"<< std::endl;
        }

};