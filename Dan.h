#pragma once

#include "BaseObject.h"
#include "ComFun.h"

class Dan : public BaseObject
{
public:
    Dan();
    ~Dan();

    enum DanDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
    };
    void set_x_val(const int& x_val) { x_val_ = x_val;}
    void set_y_val(const int& y_val) { y_val_ = y_val;}

    int get_x_val() const { return x_val_; }
    int get_y_val() const { return y_val_; }

    void set_is_move(const bool& is_move) { is_move_ = is_move; }
    bool get_is_move() const { return is_move_; }

    void set_huong_Dan(const int& huong_Dan) { huong_Dan_ = huong_Dan; }
    int get_huong_Dan() const { return huong_Dan_; }
    void HandleMove(const int& x_border, const int& y_border);// xu ly di chuyen cua dan
    
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int huong_Dan_;
};