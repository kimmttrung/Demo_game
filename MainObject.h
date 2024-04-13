#pragma once

#include "BaseObject.h"
#include "ComFun.h"

#define GRAVITY_APEED 0.6   // trọng lực
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 4

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType       // di chuyển
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
        WALK_UP = 2,
        WALK_DOWN = 3,

    };
    
    bool LoadImg(std::string path, SDL_Renderer* screen);// load hình ảnh
    void Show(SDL_Renderer* des);   // hiển thị hình ảnh
   
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);//xu ly event
   
    void set_clips();     // xu ly khung nhân vật
    //void DoPlayer(Map& map_data);// cộng trừ cho nhân vật di chuyển 

    // void CheckMap(Map& map_data);

    // void SetMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}
    // void CenterOnMap(Map& map_data);
private:

    float x_val_;       // tang bao nhieu
    float y_val_;

    
    float x_pos_;       // vi tri hien tai
    float y_pos_;

    int width_frame_;       // kich thuoc animation
    int height_frame_;

    SDL_Rect frame_clip_[8];// luu anh nhan vat
    Input input_type_;// luu trang thai
    int frame_;// chỉ só frame
    int status_;// trang thai di chuyen
    
    bool on_ground_;

    int map_x_;
    int map_y_;



};