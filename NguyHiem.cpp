#include "NguyHiem.h"

ThertsObject::ThertsObject()
{
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    come_back_time_ = 0;
    frame_ = 0;
    TrenBeMat = 0;
}
ThertsObject::~ThertsObject()
{

}
bool ThertsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret == true)
    {
        width_frame_ = rect_.w/THERT_FRAME_;
        height_frame_ = rect_.h;
    }
    return ret;
}

void ThertsObject::set_clip() // cắt hình
{
    if(width_frame_ > 0 && height_frame_ > 0)
    {
        for(int i = 0; i < THERT_FRAME_; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void ThertsObject::Show(SDL_Renderer* des)
{
    if(come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if(frame_ >= THERT_FRAME_)
        {
            frame_ = 0;
        }

        SDL_Rect* current_clip = &frame_clip_[frame_];// lấy frame hiện tại
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};// vị trí hiển thị
        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);// copy hình ảnh lên màn hình
    }
}


void ThertsObject::CheckToMap(Map& Gmap)
{
    
    int x1 = 0;// giới hạn chiều rông nhân vật  từ A -> B  (chiều ngang x)
    int x2 = 0; // 

    int y1 = 0;// giới hạn chiều cao nhân vật từ A -> B  (chiều dọc y)
    int y2 = 0;

    // check theo chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; // x1: vị trí hiện tại của nhân vật / kích thước 1 ô vuông
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min -1)/TILE_SIZE;

    /*
        x1,y1******x2,y1
        * -----------*
        * -----------*
        * -----------*
        * -----------*
        x1,y2******x2,y2
    */

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(x_val_ > 0) // di chuyển sang phải
        {
            int val1 = Gmap.tile[y1][x2];
            int val2 = Gmap.tile[y2][x2];

            if(val1 != BLANK || val2 != BLANK )
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
            
        }
        else if(x_val_ < 0) // di chuyển sang trái
        {
            int val1 = Gmap.tile[y1][x1];
            int val2 = Gmap.tile[y2][x1];

            if(val1 != BLANK || val2 != BLANK )
            {
                x_pos_ = (x1 + 1)*TILE_SIZE;
                x_val_ = 0;
            }
            
        }
    }

    // check theo chieu doc

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min )/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    /*
        x1,y1******x2,y1
        * -----------*
        * -----------*
        * -----------*
        * -----------*
        x1,y2******x2,y2
    */

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(y_val_ > 0) // rơi xuống
        {
            int val1 = Gmap.tile[y2][x1];
            int val2 = Gmap.tile[y2][x2];

            if((val1 != BLANK || val2 != BLANK ) )
            {
                y_pos_ = y2*TILE_SIZE ;// đứng trên mặt đất
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                TrenBeMat = true; // lưu trạng thái đứng trên mặt đất
            }
            
        }
        else if(y_val_ < 0) // nhảy lên 
        {
            int val1 = Gmap.tile[y1][x1];
            int val2 = Gmap.tile[y1][x2];

            if(val1 != BLANK || val2 != BLANK ){
                y_pos_ = (y1 + 1)*TILE_SIZE ;
                y_val_ = 0;
            }
            
        }
    
        x_pos_ += x_val_ ;
        y_pos_ += y_val_ ;

        if(x_pos_ < 0) x_pos_ = 0;
        else if(x_pos_ + width_frame_ > Gmap.max_x)
        {
            x_pos_ = Gmap.max_x - width_frame_ - 1;
        }
        if(y_pos_ > Gmap.max_y )
        {
            come_back_time_ = 60;
        }
    }
}

void ThertsObject::DoPlayer(Map& Gmap){
    if(come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THERT_GRAVITY_SPEED;
        if(y_val_ >= THERT_MAX_FALL_SPEED)
        {
            y_val_ = THERT_MAX_FALL_SPEED;
        }
        CheckToMap(Gmap);

    }
    else if(come_back_time_ > 0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            x_val_ = 0;
            y_val_ = 0;
            y_pos_ = 0;
            if(x_pos_ > 256)
            {
                x_pos_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            come_back_time_ = 0;
        }
    }
}
