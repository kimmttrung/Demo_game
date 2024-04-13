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

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE 64// kích thước 1 ô vuông
#define BALCK 0

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

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
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];// mảng 2 chiều lưu trữ thông tin map
    char* file_name;// tên file map

};
