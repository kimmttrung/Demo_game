#pragma once

#include "ComFun.h"
#include "BaseObject.h"

#define THERT_MAX_FALL_SPEED 10
#define THERT_GRAVITY_SPEED 0.8
#define THERT_FRAME_ 8


class ThertsObject : public BaseObject
{
    public:
        ThertsObject();
        ~ThertsObject();

    void set_x_val(const float& xVal){x_val_ = xVal;}
    void set_y_val(const float& yVal){y_val_ = yVal;}

    void set_x_pos(const float& xPos){x_pos_ = xPos;}
    void set_y_pos(const float& yPos){y_pos_ = yPos;}

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}

    void set_map_xy(const int& mp_X, const int& mp_Y){map_x_ = mp_X;map_y_ = mp_Y;}

    void set_clip();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void DoPlayer(Map& Gmap);
    void CheckToMap(Map& Gmap);

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    private:
        int map_x_;
        int map_y_;

        float x_pos_;
        float y_pos_;

        float x_val_;
        float y_val_;

        bool TrenBeMat;
        int come_back_time_;

        SDL_Rect frame_clip_[THERT_FRAME_]; 
        int width_frame_; // kích thước frame
        int height_frame_;// kích thước frame
        int frame_;

};