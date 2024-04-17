#pragma once

#include "ComFun.h"
#include "BaseObject.h"
#include "Dan.h"


#define THERT_MAX_FALL_SPEED 10
#define THERT_GRAVITY_SPEED 0.8
#define THERT_FRAME_ 8


class ThertsObject : public BaseObject
{
    public:
        ThertsObject();
        ~ThertsObject();

    enum TypeMove
    {
        STATIC_THERTS = 0,
        MOVE_THERTS = 1,
    };

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

    void set_type_move(const int& type_move){type_move_ = type_move;}// thiết lập loại di chuyển
    std::vector<Dan*> get_dan_list() const {return dan_list_;}// lấy danh sách đạn
    void set_dan_list(const std::vector<Dan*>& dl_list){dan_list_ = dl_list;}// thiết lập danh sách đạn
    
    void InitDan(Dan* p_dan, SDL_Renderer* screen);// khởi tạo đạn
    void MakeDan(SDL_Renderer* screen, const int& x_limit, const int& y_limit);// tạo đạn
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

        int type_move_;
        int animation_a_;
        int animation_b_;
        Input input_type_;

        std::vector<Dan*> dan_list_;

};