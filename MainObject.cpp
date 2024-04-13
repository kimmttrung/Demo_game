#include "MainObject.h"

MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    // input_type_.left_ = 0;
    // input_type_.right_ = 0;
    // input_type_.jump_ = 0;
    // input_type_.down_ = 0; 
    // input_type_.up_ = 0;
    bool on_ground_ = false;

}

MainObject::~MainObject()
{


}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if(ret == true)
    {
        width_frame_ = rect_.w / 8;     //60
        height_frame_ = rect_.h;        //64
    }
    return ret;

}

void MainObject::set_clips() // xử lý khung nhân vật 
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for(int i = 0; i < 8; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }

    }
}


void MainObject::Show(SDL_Renderer* des)
{
    if(status_ == WALK_LEFT){
        LoadImg("img/player_left.png", des);
    }
    else{
        LoadImg("img/player_right.png", des);
    }

    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
    }
    else {
        frame_ = 0;
    }

    if(frame_ >= 8)
    {
        frame_ = 0;
    }

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];// frame hien tai, khung hien tai
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};// đẩy lên màn hình với frame hiện tại

    //SDL_Delay(10);
    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);// load len man hinh

}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{   // bấm phím di chuyển
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT:
                {
                    status_ = WALK_RIGHT;
                    input_type_.right_ = 1;
                    input_type_.left_ = 0;
                }
                break;
            case SDLK_LEFT:
                {
                    status_ = WALK_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ = 0;
                }
                break;
            default:
                break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {   // keysym : cau truc chua thong tin qt sd su kien
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT:
                input_type_.right_ = 0;
                break;
            case SDLK_LEFT:
                input_type_.left_ = 0;
                break;
        }
    }
}

