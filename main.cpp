#include <iostream>
#include "ComFun.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "Timer.h"
#include "NguyHiem.h"

BaseObject g_background;

bool InitData()
{
    bool success = true;
    // khoi tao SDL
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    g_Window = SDL_CreateWindow("Game treasure std - kim1",
                                SDL_WINDOWPOS_UNDEFINED,   // vi tri cua screen
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);

    if(g_Window == NULL)
    {
        std::cout << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // tao render de ve hinh anh len sreeen
        // SDL_RENDERER_ACCELERATED: tang toc do phan ung
        g_screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            // sd mau cho thao tac ve
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;    
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/Bground2.jpg", g_screen);
    if(ret == false)
        return false;
    return true;
}

std::vector<ThertsObject*> MakeTherts()
{
    ThertsObject* therts_object = new ThertsObject[20];
    std::vector<ThertsObject*> list_therts;
    
    for(int i = 0; i < 20; i++)
    {
        ThertsObject* therts_object = new ThertsObject();
        therts_object->LoadImg("img/threat_level.png", g_screen); // load hình ảnh threat
        therts_object->set_clip();// cắt hình
        
        therts_object->set_x_pos(900 + i*1200);
        therts_object->set_y_pos(200);

        list_therts.push_back(therts_object);// thêm vào danh sách threat
    }

    for(int i = 0; i < 20; i++)
    {
        ThertsObject* therts_object = new ThertsObject();
        therts_object->LoadImg("img/threat_level.png", g_screen); // load hình ảnh threat
        therts_object->set_clip();// cắt hình
        
        therts_object->set_x_pos(700 + i*1500);
        therts_object->set_y_pos(800);


        list_therts.push_back(therts_object);// thêm vào danh sách threat
    }
    
    return list_therts;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{ 
    ImpTimer fps_time;

    if(InitData() == false)
        return -1;
    if(LoadBackground() == false)
        return -1;


    GameMap game_map;// khai bao map
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    game_map.LoadMap("map1/map012.dat");// load map
    #pragma GCC diagnostic warning "-Wwrite-strings"
    game_map.LoadTiles(g_screen);// load hinh anh cho map

    MainObject p_player;// khai bao animation
    p_player.LoadImg("img/player_right.png", g_screen);
    p_player.set_clips();

    std::vector<ThertsObject*> therts_list = MakeTherts();// khai bao va tao threat

    bool is_quit = false;
    while(!is_quit)
    {
        fps_time.start();
        while(SDL_PollEvent(&g_Event) != 0)
        {
            if(g_Event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputAction(g_Event, g_screen);// xử lý di chuyển nhân vật
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();// lấy thông tin map

        p_player.SetMapXY(map_data.start_x, map_data.start_y);// thiết lập vị trí map
        p_player.DoPlayer(map_data);// di chuyển nhân vật thông qua dữ liệu map truyền vào
        p_player.Show(g_screen);// hiển thị nhân vật

        game_map.SetMap(map_data);// thiết lập thông tin map
        game_map.DrawMap(g_screen);// vẽ map

        for(int i = 0; i < therts_list.size(); i++)
        {
            ThertsObject* therts = therts_list.at(i);
            if(therts != NULL)
            {
                therts->set_map_xy(map_data.start_x, map_data.start_y);
                therts->DoPlayer(map_data);// di chuyển threat
                therts->Show(g_screen);
            }
        }




        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_time.get_ticks();// thoi gian thuc te
        int time_one_frame = 1000/FRAME_PER_SECOND;// thoi gian 1 frame: 1000ms/25frame = 40ms

        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }
    
    close();
    return 0;
}
