#include "MainObject.h"



MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 448;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = 0;

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

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
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
    UpdateImage(des);

    if ((input_type_.left_ == 1) || (input_type_.right_ == 1))
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
    if(events.type == SDL_KEYDOWN)// kiểm tra sự kiện bấm phím
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_d:
                {
                    status_ = WALK_RIGHT;
                    input_type_.right_ = 1;
                    input_type_.left_ = 0;
                    UpdateImage(screen);
                }
                break;

            case SDLK_a:
                {
                    status_ = WALK_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ = 0;
                    UpdateImage(screen);
                }
                break;
            case SDLK_s:
                {
                    Dan* p_dan = new Dan();
                    p_dan->set_loai_Dan(Dan::DAN_LUA); // Change to the type of bullet you want
                    p_dan->LoadDan(screen);

                    if(status_ == WALK_LEFT)
                    {
                        p_dan->set_huong_Dan(Dan::DIR_LEFT);
                        p_dan->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
                    }
                    else
                    {
                        p_dan->set_huong_Dan(Dan::DIR_RIGHT);
                        p_dan->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
                    }

                    p_dan->set_x_val(20);
                    p_dan->set_is_move(true);

                    dan_list_.push_back(p_dan);
                }
                break;
            case SDLK_w:
                {
                    input_type_.jump_ = 1;
                }
                break;

        }
    }
    else if (events.type == SDL_KEYUP)// kiểm tra sự kiện nhả phím
    {   // keysym : cau truc chua thong tin qt sd su kien
        switch(events.key.keysym.sym)
        {
            case SDLK_d:
                input_type_.right_ = 0;
                break;
            case SDLK_a:
                input_type_.left_ = 0;
                break;
        }
    }
    if(events.type == SDL_MOUSEBUTTONDOWN) // bấm chuột nhảy
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            Dan* p_dan = new Dan();
            p_dan->set_loai_Dan(Dan::DAN_PHI); // Change to the type of bullet you want
            p_dan->LoadDan(screen);

            if(status_ == WALK_LEFT)
            {
                p_dan->set_huong_Dan(Dan::DIR_DOWN_LEFT);
                p_dan->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
            }
            else
            {
                p_dan->set_huong_Dan(Dan::DIR_DOWN_RIGHT);
                p_dan->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
            }

            p_dan->set_x_val(20);
            p_dan->set_y_val(20);
            p_dan->set_is_move(true);

            dan_list_.push_back(p_dan);
        }
        else if(events.button.button == SDL_BUTTON_RIGHT)
        {
            Dan* p_dan = new Dan();
            p_dan->set_loai_Dan(Dan::DAN_BAN);
            p_dan->LoadDan( screen);
            
            if(status_ == WALK_LEFT)
            {
                p_dan->set_huong_Dan(Dan::DIR_LEFT);
                p_dan->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
            }
            else
            {
                p_dan->set_huong_Dan(Dan::DIR_RIGHT);
                p_dan->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
            }
            
            p_dan->set_x_val(20);// tốc độ đạn
            p_dan->set_is_move(true);

            dan_list_.push_back(p_dan);
        
        }
    }
}

void MainObject::HandelDan(SDL_Renderer *des)
{
    for(int i=0;i<dan_list_.size();i++)
    {
        Dan* p_dan = dan_list_.at(i);// lấy đạn
        if(p_dan != NULL)
        {
            if(p_dan->get_is_move() == true)
            {
                p_dan->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT );
                p_dan->Render(des);
            }
            else
            {
                dan_list_.erase(dan_list_.begin() + i);// xóa đạn
                if(p_dan != NULL)
                {
                    delete p_dan;
                    p_dan = NULL;
                }
            }
        }
    }
}

void MainObject::DoPlayer(Map& map_data)// xử lý nhân vật
{
    
    if(come_back_time_ == 0){
        x_val_ = 0 ;
        y_val_ += 0.8;  // tốc độ rơi

        if (y_val_ > MAX_FALL_SPEED)  // tốc độ rơi > tốc độ rơi tối đa
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
            TrenBeMat = false;
            input_type_.jump_ = 0;
        }

        CheckMap(map_data);// kiểm tra map
        TinhToanMap(map_data);// tính toán thông số map
    }

    if(come_back_time_ > 0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            TrenBeMat = false;
            if(x_pos_ > 512) x_pos_ -= 192;// lùi 4 ô
            else x_pos_ = 448;
            if(y_pos_ > 640 && y_pos_ < 1280) 
            {
                y_pos_ = 832;
            }
            else if(y_pos_ > 1280) 
            {
                y_pos_ = 1728;
            }
            else y_pos_ = 64;
    
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
    else if (map_data.start_x + SCREEN_WIDTH > map_data.max_x)
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

void MainObject::RemoveDan(const int& idx)
{
    int size = dan_list_.size();
    if(size > 0 && idx < size)
    {
        Dan* p_dan = dan_list_.at(idx);
        dan_list_.erase(dan_list_.begin() + idx);

        if(p_dan)
        {
            delete p_dan;
            p_dan = NULL;
        }
    }
} 
std::vector<std::pair<int, int>> locked_tiles_;


void MainObject::CheckTile(Map& map_data, int x, int y)
{
    int val = map_data.tile[y][x];
    switch(val)
    {
        case KHOBAU:
            map_data.tile[y][x] = 0;
            if(MessageBoxW(NULL, L"You win", L"Thong bao",  MB_OK) == IDOK)
            {
                clean_up();
                SDL_Quit();
                exit(0);
            }
            break;
        case TAO:
            map_data.tile[y][x] = 0;
            break;
        case KEY:
            map_data.tile[y][x] = 0;
            key_count_++;
            if (!locked_tiles_.empty()) {
            auto [lock_x, lock_y] = locked_tiles_.back();
            map_data.tile[lock_y][lock_x] = 0; // Mở ô khóa
            locked_tiles_.pop_back();
            }
            if(key_count_ == 1)
            {
                map_data.tile[6][4] = 0;
            }
            else if(key_count_ == 2)
            {
                map_data.tile[13][4] = 0;
            }
            else if(key_count_ == 3)
            {
                map_data.tile[22][2] = 0;
            }

            else if(key_count_ == 4)
            {
                map_data.tile[1][5] = 0;
                map_data.tile[2][5] = 0;
                map_data.tile[3][5] = 0;
            }
            
            
            break;
        case MONEY:
            map_data.tile[y][x] = 0;
            money_count_++;
            break;
        case NGUYHIEM:
        case COC:
            come_back_time_ = 60;
            break;
        
    }
}

void MainObject::CheckMap(Map& map_data)
{

    int x1 = (x_pos_ + x_val_)/TILE_SIZE;
    int x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    int y1 = (y_pos_)/TILE_SIZE;
    int y2 = (y_pos_ + height_min -1)/TILE_SIZE;

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
            CheckTile(map_data, x2, y1);
            CheckTile(map_data, x2, y2);

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if(val1 != BLANK || val2 != BLANK )
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;

            }
        }
        else if(x_val_ < 0) // di chuyển sang trái
        {
            CheckTile(map_data, x1, y1);
            CheckTile(map_data, x1, y2);

            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

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

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(y_val_ > 0) // rơi xuống
        {
            CheckTile(map_data, x1, y2);
            CheckTile(map_data, x2, y2);

            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 != BLANK || val2 != BLANK )
            {
                y_pos_ = y2*TILE_SIZE ;// đứng trên mặt đất
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                TrenBeMat = true;// lưu trạng thái đứng trên mặt đất
            }
            
        }
        else if(y_val_ < 0) // nhảy lên 
        {
            CheckTile(map_data, x1, y1);
            CheckTile(map_data, x2, y1);

            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 != BLANK || val2 != BLANK )
            {
                y_pos_ = (y1 + 1)*TILE_SIZE;
                y_val_ = 0;
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
    if(y_pos_ > map_data.max_y )
    {
        come_back_time_ = 30;
    }
}


// void MainObject::CheckMap(Map& map_data)
// {

//     int x1 = 0;// giới hạn chiều rông nhân vật  từ A -> B  (chiều ngang x)
//     int x2 = 0; 

//     int y1 = 0;// giới hạn chiều cao nhân vật từ A -> B  (chiều dọc y)
//     int y2 = 0;

//     // check theo chieu ngang
//     int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

//     x1 = (x_pos_ + x_val_)/TILE_SIZE; // x1: vị trí hiện tại của nhân vật / kích thước 1 ô vuông
//     x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

//     y1 = (y_pos_)/TILE_SIZE;
//     y2 = (y_pos_ + height_min -1)/TILE_SIZE;

//     /*
//         x1,y1******x2,y1
//         * -----------*
//         * -----------*
//         * -----------*
//         * -----------*
//         x1,y2******x2,y2
//     */

//     if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
//     {
//         if(x_val_ > 0) // di chuyển sang phải
//         {
//             int val1 = map_data.tile[y1][x2];
//             int val2 = map_data.tile[y2][x2];

//             if(val1 == KHOBAU || val2 == KHOBAU)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
                
//                 if(MessageBoxW(NULL, L"You win", L"Thong bao",  MB_OK) == IDOK)
//                 {
//                     clean_up();
//                     SDL_Quit();
//                     exit(0);
//                 }
                
//             }
//             else if(val1 == TAO || val2 == TAO)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;

//             }
//             else if(val1 == KEY || val2 == KEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 key_count_++;
//             }
//             else if(val1 == MONEY || val2 == MONEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 money_count_++;
//             }
//             else 
//             {
//                 if(val1 != BLANK || val2 != BLANK )
//                 {
//                     x_pos_ = x2*TILE_SIZE;
//                     x_pos_ -= width_frame_ + 1;
//                     x_val_ = 0;

//                 }
//             }
            
//             if(val1 == NGUYHIEM || val2 == NGUYHIEM)
//             {
//                 come_back_time_ = 60;
//             }
//             if(val1 == COC || val2 == COC)
//             {
//                come_back_time_ = 60;
//             }
            
//         }
//         else if(x_val_ < 0) // di chuyển sang trái
//         {
//             int val1 = map_data.tile[y1][x1];
//             int val2 = map_data.tile[y2][x1];

//             if(val1 == KHOBAU || val2 == KHOBAU)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
                
//                 if(MessageBoxW(NULL, L"You win", L"Thong bao",  MB_OK) == IDOK)
//                 {
//                     clean_up();
//                     SDL_Quit();
//                     exit(0);
//                 }
                
//             }
//             else if(val1 == TAO || val2 == TAO)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;

//             }
//             else if(val1 == KEY || val2 == KEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 key_count_++;
//             }
//             else if(val1 == MONEY || val2 == MONEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 money_count_++;
//             }
//             else{
//                 if(val1 != BLANK || val2 != BLANK )
//                 {
//                     x_pos_ = (x1 + 1)*TILE_SIZE;
//                     x_val_ = 0;
//                 }
//             }

//             if(val1 == NGUYHIEM || val2 == NGUYHIEM)
//             {
//                 come_back_time_ = 60;
//             }
//             if(val1 == COC || val2 == COC)
//             {
//                come_back_time_ = 60;
//             }
//         }
//     }

//     // check theo chieu doc

//     int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
//     x1 = (x_pos_)/TILE_SIZE;
//     x2 = (x_pos_ + width_min )/TILE_SIZE;

//     y1 = (y_pos_ + y_val_)/TILE_SIZE;
//     y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

//     /*
//         x1,y1******x2,y1
//         * -----------*
//         * -----------*
//         * -----------*
//         * -----------*
//         x1,y2******x2,y2
//     */

//     if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
//     {
//         if(y_val_ > 0) // rơi xuống
//         {
//             int val1 = map_data.tile[y2][x1];
//             int val2 = map_data.tile[y2][x2];

//             if(val1 == KHOBAU || val2 == KHOBAU)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
                
//                 if(MessageBoxW(NULL, L"You win", L"Thong bao",  MB_OK) == IDOK)
//                 {
//                     clean_up();
//                     SDL_Quit();
//                     exit(0);
//                 }
                
//             }
//             else if(val1 == TAO || val2 == TAO)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
                
//             }
//             else if(val1 == KEY || val2 == KEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 key_count_++;
//             }
//             else if(val1 == MONEY || val2 == MONEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 money_count_++;
//             }
//             else{
//                 if(val1 != BLANK || val2 != BLANK )
//                 {
//                     y_pos_ = y2*TILE_SIZE ;// đứng trên mặt đất
//                     y_pos_ -= (height_frame_ + 1);
//                     y_val_ = 0;
//                     TrenBeMat = true; // lưu trạng thái đứng trên mặt đất
//                 }
//             }

//             if(val1 == NGUYHIEM || val2 == NGUYHIEM)
//             {
//                 come_back_time_ = 60;
//             }
//             if(val1 == COC || val2 == COC)
//             {
//                come_back_time_ = 60;
//             }
//         }
//         else if(y_val_ < 0) // nhảy lên 
//         {
//             int val1 = map_data.tile[y1][x1];
//             int val2 = map_data.tile[y1][x2];

//             if(val1 == KHOBAU || val2 == KHOBAU)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
                
//                 if(MessageBoxW(NULL, L"You win", L"Thong bao",  MB_OK) == IDOK)
//                 {
//                     clean_up();
//                     SDL_Quit();
//                     exit(0);
//                 }
                
//             }
//             else if(val1 == TAO || val2 == TAO)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
                
//             }
//             else if(val1 == KEY || val2 == KEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 key_count_++;
                
//             }
//             else if(val1 == MONEY || val2 == MONEY)
//             {
//                 map_data.tile[y1][x2] = 0;
//                 map_data.tile[y2][x2] = 0;
//                 money_count_++;
//             }
//             else{
//                 if(val1 != BLANK || val2 != BLANK )
//                 {
//                     y_pos_ = (y1 + 1)*TILE_SIZE ;
//                     y_val_ = 0;
//                 }
//             }
        
//             if(val1 == NGUYHIEM || val2 == NGUYHIEM)
//             {
//                 come_back_time_ = 60;
//             }
//             if(val1 == COC || val2 == COC)
//             {
//                come_back_time_ = 60;
//             }

//         }
    

//         x_pos_ += x_val_ ;
//         y_pos_ += y_val_ ;

//         if(x_pos_ < 0) x_pos_ = 0;
//         else if(x_pos_ + width_frame_ > map_data.max_x)
//         {
//             x_pos_ = map_data.max_x - width_frame_ - 1;
//         }
//         if(y_pos_ > map_data.max_y )
//         {
//             come_back_time_ = 30;
//         }
//     }
// }



void MainObject::UpdateImage(SDL_Renderer* des)
{
    if(TrenBeMat == true)
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("img/player_left1.png", des);
        }
        else
        {
            LoadImg("img/player_right1.png", des);
        }
    }
    else
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("img/jum_left1.png", des);
        }
        else
        {
            LoadImg("img/jum_right1.png", des);
        }
    }
}

void MainObject::clean_up()
{
    
    // Destroy renderer
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    // Destroy window
    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}