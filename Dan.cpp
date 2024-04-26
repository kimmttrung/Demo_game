#include "Dan.h"

Dan::Dan()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    loai_Dan_ = DAN_BAN;
}

Dan::~Dan()
{

}
void Dan::LoadDan(SDL_Renderer* des)
{
    if(loai_Dan_ == DAN_BAN)
    {
        LoadImg("Image/img/dan1.png", des);
    }
    else if(loai_Dan_ == DAN_BAN_LASER)
    {
        LoadImg("Image/img/laser2.png", des);
    }
    else if(loai_Dan_ == DAN_LUA)
    {
        LoadImg("Image/img/dan4.png", des);
    }
    else if(loai_Dan_ == DAN_PHI)
    {
        LoadImg("Image/img/dan5.png", des);
    }
    
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
    else if(huong_Dan_ == DIR_DOWN_RIGHT)
    {
        rect_.x += x_val_;
        rect_.y += y_val_;
        if(rect_.x > x_border || rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
    else if(huong_Dan_ == DIR_DOWN_LEFT)
    {
        rect_.x -= x_val_;
        rect_.y += y_val_;
        if(rect_.x < 0 || rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}