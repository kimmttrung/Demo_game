#include "Dan.h"

Dan::Dan()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

Dan::~Dan()
{

}

void Dan::HandleMove(const int& x_border, const int& y_border)
{
    if(huong_Dan_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if(rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if(huong_Dan_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if(rect_.x < 0)
        {
            is_move_ = false;
        }
    }
    
}