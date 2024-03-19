#pragma once

#include "BaseObject.h"
#include "func.h"

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };
    // thong so rin
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    // xu ly event
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    // xu ly nhan vat
    void set_clips();
private:
    // tang bao nhieu
    float x_val_;
    float y_val_;

    // vi tri hien tai
    float x_pos_;
    float y_pos_;

    // kich thuoc nhan vat
    int width_frame_;
    int height_frame_;

    // luu anh nhan vat
    SDL_Rect frame_clip_[8];
    // luu trang thai
    Input input_type_;
    int frame_;
    // trang thai di chuyen
    int status_;

};