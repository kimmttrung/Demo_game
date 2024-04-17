#pragma once

#include "BaseObject.h"
#include "ComFun.h"
#include <vector>
#include "Dan.h"

#define GRAVITY_APEED 0.8   // trọng lực rơi
#define MAX_FALL_SPEED 10   // tốc độ rơi tối đa
#define PLAYER_SPEED 15      // tốc độ di chuyển nhân vật
#define PLAYER_JUMP_VAL 20  // tốc độ nhảy
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType       // di chuyển
    {
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };
    
    bool LoadImg(std::string path, SDL_Renderer* screen);// load hình ảnh
    void Show(SDL_Renderer* des);   // hiển thị hình ảnh
   
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);//xu ly event
    void set_clips();     // xu ly khung nhân vật

    void DoPlayer(Map& map_data);// cộng trừ cho nhân vật di chuyển 
    void CheckMap(Map& map_data);// kiểm tra map

    void SetMapXY(const int map_x, const int map_y){map_x_ = map_x; map_y_ = map_y;}// thiết lập vị trí map
    void TinhToanMap(Map& map_data); // tính toán thông số bản đồ 
    void IncreaseMoney();// tăng tiền 
    void UpdateImage(SDL_Renderer* des);// cập nhật hình ảnh nhân vật
    void set_dan_list(std::vector<Dan*> dan_list){dan_list_ = dan_list;}// thiết lập danh sách đạn
    std::vector<Dan*> get_dan_list() const {return dan_list_;}// lấy danh sách đạn
    void HandelDan(SDL_Renderer *des); 
private:
    std::vector<Dan*> dan_list_;    // danh sách đạn

    int money_count_;   // số tiền ăn đuọc
    int key_count_;     // số chìa khóa

    float x_val_;       // tang bao nhieu
    float y_val_;

    
    float x_pos_;       // vi tri hien tai
    float y_pos_;

    int width_frame_;     // kich thuoc animation
    int height_frame_;

    SDL_Rect frame_clip_[8];// luu anh nhan vat
    Input input_type_;// luu trang thai
    int frame_;// chỉ só frame
    int status_;// trang thai di chuyen
    
    bool TrenBeMat;// kiem tra nhân vật có đang ở trên mặt đất không

    int map_x_;// vị trí map mới sau khi di chuyển
    int map_y_;

    int come_back_time_; // thời gian quay lại

};