#pragma once
#include<iostream>
#include<string>

class Vector
{
public:
    float X, Y;
public:
    Vector(float x = 0, float y = 0): X(x), Y(y) {}

public:
    inline Vector operator+(const Vector &v2) const{
        return Vector(X + v2.X, Y + v2.Y);
    }
    inline Vector operator-(const Vector &v2) const{
        return Vector(X - v2.X, Y - v2.Y);
    }

    inline Vector operator*(const float voHuong) const{
        return Vector(X*voHuong, Y*voHuong);
    }

    void Log(std::string mag = ""){
        std::cout << mag << "(X Y) = (" << X << " " << Y  << ")" << std::endl;
    }
};