#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


static SDL_Window* g_Window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_Event;

// SDL_Surface: là 1 cấu trúc hìn ảnh chứ pixel: tạo, vẽ, xóa, chuyển đổi, lưu, tải, ...
// SDL_Renderer: là 1 cấu trúc vẽ hình ảnh, nó giúp vẽ hình ảnh lên màn hình và hỗ trợ tăng tốc độ vẽ hình ảnh
// khác biệt lớn nhất : hỗ trợ tăng tốc độ vẽ hình ảnh(SDL_Renderer)
// static: giữ giá trị của biến trong suốt chương trình
// SCREEN_BPP: số bit màu cho mỗi pixel
// RENDER_DRAW_COLOR: màu vẽ mặc định

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 960;
const int SCREEN_BPP = 32;

const int FRAME_PER_SECOND = 25;// trong 1s chạy đc 25 frame(càng nhỏ -> chương trình chạy càng chậm)
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE 64// kích thước 1 ô vuông

#define BLANK 0 // trạng thái bằng 0
#define KHOBAU 11 // kho báu
#define MONEY 4 // tiền
#define KEY 10 // chìa khóa
#define TREE1 5 // cây1
#define TREE2 13 // cây2
#define HEART 14 // trái tim
#define NGUYHIEM 7 // nước 
#define COC 3// cọc
#define MAX_MAP_X 210
#define MAX_MAP_Y 30


struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

struct Map // lưu trữ thông tin map
{
    int start_x;// đầu map
    int start_y;

    int max_x;// cuối map
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];// mảng 2 chiều lưu trữ thông tin map
    char* file_name;// tên file map

};

namespace SDLCommonFunc
{
    bool CheckVaCham(const SDL_Rect& object1, const SDL_Rect& object2);// kiểm tra va chạm
}
