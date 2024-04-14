#include "MainObject.h"

MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 448;
    y_pos_ = 448;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;

    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.down_ = 0; 
    input_type_.up_ = 0;

    bool TrenBeMat = false;

    map_x_ = 0;
    map_y_ = 0;
    money_count_ = 0;

    come_back_time_ = 0;
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

void MainObject::IncreaseMoney()
{
    money_count_++;
    key_count_++;

}
void MainObject::Show(SDL_Renderer* des)
{
    if(TrenBeMat == true)
    {
        y_val_ += GRAVITY_APEED;
        if(status_ == WALK_LEFT){
        LoadImg("img/player_left.png", des);
        }
        else{
            LoadImg("img/player_right.png", des);
        }
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
    if(come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_];// frame hien tai, khung hien tai
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};// đẩy lên màn hình với frame hiện tại

        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);// load len man hinh

    }
    
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
                    if(TrenBeMat == true) LoadImg("img/player_right.png", screen);
                    else LoadImg("img/jum_right.png", screen);
                    
                }
                break;

            case SDLK_LEFT:
                {
                    status_ = WALK_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ = 0;
                    if(TrenBeMat == true) LoadImg("img/left_right.png", screen);
                    else LoadImg("img/jum_left.png", screen);
                }
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
    if(events.type == SDL_MOUSEBUTTONDOWN) // bấm chuột nhảy
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            input_type_.jump_ = 1;
        }
    }
}

void MainObject::DoPlayer(Map& map_data)
{
    if(come_back_time_ == 0){
        x_val_ = 0 ;
        y_val_ += 0.8;  // tốc độ rơi

        if (y_val_ >= MAX_FALL_SPEED)  // tốc độ rơi > tốc độ rơi tối đa
        {
            y_val_ = MAX_FALL_SPEED;
        }
        if (input_type_.left_ == 1)
        {
            x_val_ -= PLAYER_SPEED;
        }
        else if(input_type_.right_ == 1)
        {
            x_val_ += PLAYER_SPEED;
        }

        if(input_type_.jump_ == 1)
        {
            if(TrenBeMat == true)
            {
                y_val_ = -PLAYER_JUMP_VAL;
            }
            input_type_.jump_ = 0;
            TrenBeMat = false;
        }

        CheckMap(map_data);// kiểm tra map
        TinhToanMap(map_data);// tính toán thông số map
    }
    if(come_back_time_ > 0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            if(x_pos_ > 256)
            {
                x_pos_ -= 256;// lùi 4 ô
                map_x_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
    }

}

void MainObject::TinhToanMap(Map& map_data)
{
    map_data.start_x = x_pos_ - (SCREEN_WIDTH / 2);// vị trí bắt đầu map
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos_ - (SCREEN_HEIGHT / 2);// vị trí bắt đầu map
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }

}


void MainObject::CheckMap(Map& map_data)
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

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) // di chuyển sang phải
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if(val1 == MONEY || val2 == MONEY || val1 == KEY || val2 == KEY)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
            }
            else
            {
                if(val1 != BLANK || val2 != BLANK)
                {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1;
                    x_val_ = 0;
                }
            }
            
        }
        else if(x_val_ < 0) // di chuyển sang trái
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 == MONEY || val2 == MONEY || val1 == KEY || val2 == KEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseMoney();
            }
            else{
                if(val1 != BLANK || val2 != BLANK)
                {
                    x_pos_ = (x1 + 1)*TILE_SIZE;
                    x_val_ = 0;
                }
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

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0) // rơi xuống
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 == MONEY || val2 == MONEY || val1 == KEY || val2 == KEY)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
            }
            else{
                if(val1 != BLANK || val2 != BLANK)
                {
                    y_pos_ = y2*TILE_SIZE ;// đứng trên mặt đất
                    y_pos_ -= (height_frame_ + 1);
                    y_val_ = 0;
                    TrenBeMat = true; // lưu trạng thái đứng trên mặt đất
                }
            }
        }
        else if(y_val_ < 0) // nhảy lên 
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == MONEY || val2 == MONEY || val1 == KEY || val2 == KEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseMoney();
            }
            else{
                if(val1 != BLANK || val2 != BLANK)
                {
                    y_pos_ = (y1 + 1)*TILE_SIZE ;
                    y_val_ = 0;
                }
            }
        }
    }

    x_pos_ += x_val_ ;
    y_pos_ += y_val_ ;

    if(x_pos_ < 0) x_pos_ = 0;
    else if(x_pos_ + width_frame_ > map_data.max_x)
    {
        x_pos_ = map_data.max_x - width_frame_ - 1;
    }
    if(y_pos_ > map_data.max_y)
    {
        come_back_time_ = 60;
    }
}
