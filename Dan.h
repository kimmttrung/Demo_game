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

    enum
    {
        DAN_BAN = 23,
        DAN_BAN_LASER = 24,
        DAN_LUA = 25,
    };

    void set_x_val(const int& x_val) { x_val_ = x_val;}// thiết lập giá trị x
    void set_y_val(const int& y_val) { y_val_ = y_val;}// thiết lập giá trị y

    int get_x_val() const { return x_val_; }
    int get_y_val() const { return y_val_; }

    void set_is_move(const bool& is_move) { is_move_ = is_move; }// thiết lập di chuyển
    bool get_is_move() const { return is_move_; }// lấy trạng thái di chuyển

    void set_huong_Dan(const int& huong_Dan) { huong_Dan_ = huong_Dan; }// thiết lập hướng di chuyển
    int get_huong_Dan() const { return huong_Dan_; }// lấy hướng di chuyển

    void HandleMove(const int& x_border, const int& y_border);// xu ly di chuyen cua dan
    
    void set_loai_Dan(const int& loai_Dan) { loai_Dan_ = loai_Dan; }// thiết lập loại đạn
    int get_loai_Dan() const { return loai_Dan_; }// lấy loại đạn

    void LoadDan(SDL_Renderer* des);// load đạn
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int huong_Dan_;
    int loai_Dan_;
};